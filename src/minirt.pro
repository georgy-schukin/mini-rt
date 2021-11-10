TEMPLATE = subdirs

#CONFIG += ordered

SUBDIRS = \
    minirt \
    test 

minirt.subdir = minirt
test.subdir = test

test.depends = minirt


