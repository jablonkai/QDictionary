SUBDIRS += src
TEMPLATE = subdirs 
CONFIG += warn_on \
          qt \
          thread 
OTHER_FILES += \
    CMakeLists.txt