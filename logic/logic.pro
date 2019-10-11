TEMPLATE = subdirs

SUBDIRS += \
    cpp_gui \
    module \
    src \
    test

test.depends = src
module.depends = src
cpp_gui.depends = src
