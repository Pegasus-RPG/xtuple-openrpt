Name: openrpt
Version: 3.3.7
Release: 1%{?dist}
Summary: xTuple reporting utility and libraries
License: CPAL
Url: http://www.xtuple.com/openrpt/
Source: https://github.com/xtuple/openrpt/archive/v%version.tar.gz
BuildRequires: qt-devel
BuildRequires: libdmtx-devel

%description
Graphical SQL report writer, designer and rendering engine, optimized
for PostgreSQL. WYSIWYG display, GUI built with Qt. Reports can be saved
as XML, either as files or in a database.

%package libs
Summary: Shared libraries for OpenRPT

%description libs
Graphical SQL report writer, designer and rendering engine, optimized
for PostgreSQL. WYSIWYG display, GUI built with Qt. Reports can be saved
as XML, either as files or in a database.
This package provides the core libraries: libopenrpt

%package devel
Summary: OpenRPT development files
Requires: %{name}-libs%{?_isa} = %{version}-%{release}, qt-devel, libdmtx-devel

%description devel
Graphical SQL report writer, designer and rendering engine, optimized
for PostgreSQL. WYSIWYG display, GUI built with Qt. Reports can be saved
as XML, either as files or in a database.
This package provides the header files used by developers.

%prep
%setup -q

%build
export USE_SYSTEM_DMTX=1
lrelease-qt4 */*/*.ts */*.ts
qmake-qt4 .
make %{?_smp_mflags}

%install
# make install doesn't do anything for this qmake project so we do
# the installs manually
#make INSTALL_ROOT=%{buildroot} install
rm -f %{buildroot}%{_libdir}/lib*.a
rm -f %{buildroot}%{_libdir}/lib*.la
mv bin/graph bin/openrpt-graph
mkdir -p %{buildroot}%{_bindir}
install bin/* %{buildroot}%{_bindir}
mkdir -p %{buildroot}%{_libdir}
cp -dp lib/lib*.so* %{buildroot}%{_libdir}
mkdir -p %{buildroot}%{_includedir}/openrpt
find . -name '*.h' -exec install -D {} %{buildroot}%{_includedir}/openrpt/{} \;
mkdir -p %{buildroot}%{_datadir}/openrpt/OpenRPT/images
cp -r OpenRPT/images/* %{buildroot}%{_datadir}/openrpt/OpenRPT/images

%post
/sbin/ldconfig

%post libs -p /sbin/ldconfig

%postun
/sbin/ldconfig

%postun libs -p /sbin/ldconfig

%clean
rm -rf $RPM_BUILD_ROOT

%files 
%{_bindir}/*

%files libs
%doc COPYING
%{_libdir}/lib*.so.*

%files devel
%dir %{_includedir}/openrpt/
%{_includedir}/openrpt/*
%{_libdir}/libopenrptcommon.so
%{_libdir}/libMetaSQL.so
%{_libdir}/librenderer.so
%{_libdir}/libwrtembed.so
%dir %{_datadir}/openrpt/OpenRPT/images
%{_datadir}/openrpt/OpenRPT/images/*

%changelog
* Wed Feb 25 2015 Daniel Pocock <<daniel@pocock.pro> - 3.3.7-1
- Initial RPM packaging.

