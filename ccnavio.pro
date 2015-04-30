TEMPLATE = subdirs

SUBDIRS += \
    lib \
    include \
    demo \
    modules \
    ext

lib.depends     = include
demo.depends    = lib
modules.depends = ext
modules.depends = lib

