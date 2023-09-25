/* config.h */
#define USE_REGEX
#define USE_TIGGE
//#define DISABLE_ALARM
//#define DISABLE_STAT
#define USE_NAMES NCEP
//#define USE_UDF
#define IPOLATES_LIB "ip2lib_d"
#define USE_IPOLATES 3
#define USE_OPENMP
#define CPPFLAGS " -I/cpc/home/wd51we/grib2/include -Wall -Wmissing-prototypes -Wold-style-definition -Werror=format-security -ffast-math -O3 -DGFORTRAN -fopenmp"
#define FFLAGS " -c -O3 -fopenmp"
//#define USE_G2CLIB
#define USE_PROJ4
#define USE_JASPER
//#define USE_AEC
#define USE_SPECTRAL 1
#define USE_NETCDF3
//#define USE_MYSQL
#define CC "gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)"
#define FORTRAN "GNU Fortran (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)"
#define BUILD_COMMENTS "stock build"
#define USE_PNG
//#define WMO_VALIDATION
