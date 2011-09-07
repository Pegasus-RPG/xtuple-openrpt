/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2011 by OpenMFG, LLC
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

#ifndef __METASQLQUERYPARSER_H__
#define __METASQLQUERYPARSER_H__

#include <sstream>
#include <string>
#include <list>
#include <map>

class MetaSQLBlock;

class MetaSQLInfo {
    public:
        MetaSQLInfo() {}
        virtual ~MetaSQLInfo() {}

        virtual std::string trueValue() { return "true"; }
        virtual std::string falseValue() { return "false"; }

        virtual void setValuePos(const std::string & name, int pos) {
            _posList[name] = pos;
        }

        virtual int getValuePos(const std::string & name) {
            int pos = 0;
            if(_posList.count(name) > 0)
              pos = _posList[name];
            return pos;
        }

        virtual std::list<std::string> enumerateNames() = 0;
        virtual bool isValueFirst(const std::string &) = 0;
        virtual bool isValueLast(const std::string &) = 0;
        virtual int getValueListCount(const std::string & name) = 0;
	virtual std::string getValue(const std::string & name, bool param = false, int pos = -1) = 0;

    protected:
        std::map<std::string, int> _posList;
};

class MetaSQLQueryParser { 
    public:
        MetaSQLQueryParser() {
            _valid = false;
            _top = 0;
        }
        virtual ~MetaSQLQueryParser();

        bool isValid() { return _valid; }
        std::string errors() const { return _logger.str(); }

        bool parse_query(const std::string & query);

        std::string populate(MetaSQLInfo *);

        std::stringstream _logger;

    private:
        bool _valid;
        MetaSQLBlock * _top;

};

#endif // __METASQLQUERYPARSER_H__
