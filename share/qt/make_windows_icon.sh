#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/skullcash.ico

convert ../../src/qt/res/icons/skullcash-16.png ../../src/qt/res/icons/skullcash-32.png ../../src/qt/res/icons/skullcash-48.png ${ICON_DST}
