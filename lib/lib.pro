TEMPLATE = subdirs

SUBDIRS += \
    kernel \
    test

test.depends = kernel
