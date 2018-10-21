APP_ABI := all
#APP_ABI := armeabi-v7a

APP_CPPFLAGS += \
	-D__STDC_CONSTANT_MACROS \
    -D__STDC_LIMIT_MACROS \
    -D__STDC_FORMAT_MACROS \
    -D__DEBUG__ \
    -std=gnu99 \
    -Wno-pmf-conversions \
    -fno-rtti \
    -fno-exceptions \
    -Dtypeof=decltype \

APP_CPPFLAGS += -O2 -Wall -Wextra -flto=3 -fvisibility=hidden

APP_LDFLAGS += \
    -Wl,--exclude-libs=ALL \

APP_STL := c++_static

APP_OPTIM   := release

APP_MODULES := liblua luajava

#NDK_TOOLCHAIN_VERSION := 4.9
APP_PLATFORM 	:= android-14