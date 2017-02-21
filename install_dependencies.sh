#!/bin/bash
export ENV_ROOT="${TRAVIS_BUILD_DIR}/deps"
export ENV_TMP="${TRAVIS_BUILD_DIR}/tmp"

if [ -z "$ENV_ROOT" ]; then
    export ENV_ROOT=`realpath ..`/root
fi
if [ ! -d "$ENV_ROOT" ]; then
    mkdir -p $ENV_ROOT
fi
if [ -z "$ENV_TMP" ]; then
    export ENV_TMP=`realpath ..`/tmp
fi
if [ ! -d "$ENV_TMP" ]; then
    mkdir -p $ENV_TMP
fi
rm -rf $ENV_TMP/*



# ----------------------------------------------------------
#
# Python installation
#
pushd $ENV_TMP
wget http://sqlite.org/2017/sqlite-autoconf-3160200.tar.gz
tar xfz sqlite-autoconf-3160200.tar.gz
pushd sqlite-autoconf-3160200
./configure --prefix=${ENV_ROOT} --disable-static   CFLAGS="-g -O2 -DSQLITE_ENABLE_FTS3=1  -DSQLITE_ENABLE_COLUMN_METADATA=1  -DSQLITE_ENABLE_UNLOCK_NOTIFY=1  -DSQLITE_SECURE_DELETE=1 -DSQLITE_ENABLE_DBSTAT_VTAB=1" 
make -j8
make install
popd 
popd
export LD_LIBRARY_PATH=${ENV_ROOT}/lib:${LD_LIBRARY_PATH}
pushd $ENV_TMP
wget https://www.python.org/ftp/python/3.6.0/Python-3.6.0.tar.xz
unxz Python-3.6.0.tar.xz
tar xf Python-3.6.0.tar
pushd Python-3.6.0
./configure --prefix=${ENV_ROOT}  --enable-shared --with-ensurepip --enable-loadable-sqlite-extensions --enable-optimization
make -j8
make install
popd
rm Python-3.6.0.tar
popd
ln -s $ENV_ROOT/lib $ENV_ROOT/lib64
ln -s $ENV_ROOT/bin/python3 $ENV_ROOT/bin/python
ln -s $ENV_ROOT/bin/pip3 $ENV_ROOT/bin/pip


# ----------------------------------------------------------
#
# cmake installation
#

pushd $ENV_TMP
wget https://cmake.org/files/v3.8/cmake-3.8.0-rc1.tar.gz
tar xvfz cmake-3.8.0-rc1.tar.gz
pushd cmake-3.8.0-rc1
./configure --prefix=${ENV_ROOT} 
make -j8 install
popd 
popd
touch cmake.install

echo export ENV_ROOT=$ENV_ROOT > $ENV_ROOT/environment
echo export CMAKE_ROOT=${ENV_ROOT}/share/cmake-3.8 >> $ENV_ROOT/environment
echo export PYTHONPATH=${ENV_ROOT}/lib/python3.6:${ENV_ROOT}/lib/python3.6/site-packages >> $ENV_ROOT/environment

cat environment >> $ENV_ROOT/environment

source ${ENV_ROOT}/environment
$ENV_ROOT/bin/pip install -U pip
$ENV_ROOT/bin/pip install numpy 
$ENV_ROOT/bin/pip install -r requirements.txt

pushd $ENV_TMP
git clone https://github.com/pybind/pybind11.git
pushd  pybind11
$ENV_ROOT/bin/python setup.py install  
cp -fr ./include/pybind11/ ${ENV_ROOT}/include/python3.6m
popd 
popd 
touch pybind11.install


# ----------------------------------------------------------
#
# Installing basic environment
#
shopt -s nullglob


#################gsl
pushd $ENV_TMP

wget ftp://ftp.gnu.org/gnu/gsl/gsl-2.3.tar.gz
tar xzf gsl-2.3.tar.gz
cd gsl-2.3
./configure --prefix=${ENV_ROOT}
make -j7
make install

#########Frame
pushd $ENV_TMP
wget http://lappweb.in2p3.fr/virgo/FrameL/libframe-8.30.tar.gz
tar xfz libframe-8.30.tar.gz
cd libframe-8.30
./configure --prefix=${ENV_ROOT}
make VERBOSE=0
make install
cp -fr ./src/Fr*.h ${ENV_ROOT}/include 
export PATH=${ENV_ROOT}/bin:{PATH}
export LD_LIBRARY_PATH=${ENV_ROOT}/lib:${LD_LIBRARY_PATH}        


source ${ENV_ROOT}/environment
