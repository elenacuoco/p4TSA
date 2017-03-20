

#!/usr/bin/env
bash binder --root-module pytsa  --prefix=./python-wrapper/ --single-file ./include/tsa.hpp --bind tsa --skip std -skip boost -I./include -I./src -I./include/eternity -I$ENV_ROOT/include -I$ENV_ROOT/include/boost -I$ENV_ROOT/include/gsl \ -DMY_PROJECT_DEFINE -DNDEBUG

