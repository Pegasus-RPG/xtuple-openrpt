/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2014 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#include "dbtools.h"

#include <QUrl>

void parseDatabaseURL(const QString &pDatabaseURL, QString & pProtocol, QString &pServer, QString &pDatabase, QString &pPort)
{
  int location;

  QUrl url(pDatabaseURL);
  pProtocol = url.scheme();
  pServer = url.host();
  pDatabase = url.path();
  if(pDatabase.startsWith("/"))
    pDatabase = pDatabase.mid(1);
  int port = url.port();
  if(port <= 0)
  {
    // If the port is not specified it may be the old style so lets check
    // for it in the database path like we used to do
    location = pDatabase.indexOf(":");
    if(-1 != location)
    {
      port = pDatabase.right(pDatabase.length() - location - 1).toInt();
      pDatabase = pDatabase.left(location);
    }
  }
  if(port <= 0)
    port = 5432;
  pPort = QString().setNum(port);
}

void buildDatabaseURL(QString &pTarget, const QString & pProtocol, const QString &pServer, const QString &pDatabase, const QString &pPort)
{
  pTarget = pProtocol + "://" + pServer + ":" + pPort + "/" + pDatabase;
}

QString normalizeProtocol(QString protocol)
{
  QString result;
  if( "odbc" == protocol )
    result = "QODBC";
  else if ( "pgsql" == protocol || "psql" == protocol )
    result = "QPSQL";
  else if ( "db2" == protocol )
    result = "QDB2";
  else if ( "ibase" == protocol )
    result = "QIBASE";
  else if ( "mysql" == protocol )
    result = "QMYSQL";
  else if ( "oracle" == protocol )
    result = "QOCI";
  else if ( "sqlite" == protocol )
    result = "QSQLITE";
  else if ( "sqlite2" == protocol )
    result = "QSQLITE2";
  else if ( "sybase" == protocol )
    result = "QTDS";
  else
    result = protocol.toUpper(); // third-party or custom qt SQL drivers

  return result;
}

QSqlDatabase databaseFromURL( const QString& databaseURL )
{
  QString protocol;
  QString hostName;
  QString dbName;
  QString port;

  parseDatabaseURL( databaseURL, protocol, hostName, dbName, port );
  QSqlDatabase db = QSqlDatabase::addDatabase(normalizeProtocol(protocol));
  if ( db.isValid() )
  {
    db.setDatabaseName(dbName);
    db.setHostName(hostName);
    // Check if port was provided. If not, let Qt decide, it knows default values.
    bool ok;
    int iport = port.toInt( &ok );
    if ( ok )
      db.setPort( iport );
  }
  return db;
}
