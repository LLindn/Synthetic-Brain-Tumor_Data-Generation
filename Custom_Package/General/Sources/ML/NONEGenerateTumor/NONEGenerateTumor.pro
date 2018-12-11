# -----------------------------------------------------------------------------
# NONEGenerateTumor project profile
#
# \file
# \author  LL
# -----------------------------------------------------------------------------


TEMPLATE   = lib
TARGET     = NONEGenerateTumor

DESTDIR    = $$(MLAB_CURRENT_PACKAGE_DIR)/lib
DLLDESTDIR = $$(MLAB_CURRENT_PACKAGE_DIR)/lib

# Set high warn level (warn 4 on MSVC)
WARN = HIGH

# Add used projects here (see included pri files below for available projects)
CONFIG += dll ML inventor MLBase MLTools

MLAB_PACKAGES += CostumeModules_General \
                 MeVisLab_Standard

# make sure that this file is included after CONFIG and MLAB_PACKAGES
include ($(MLAB_MeVis_Foundation)/Configuration/IncludePackages.pri)

DEFINES += NONEGENERATETUMOR_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    NONEGenerateTumorInit.h \
    NONEGenerateTumorSystem.h \
    mlGenerateTumor.h \
    CtPolyhedron.h \

SOURCES += \
    NONEGenerateTumorInit.cpp \
    mlGenerateTumor.cpp \
    CtPolyhedron.cpp \
