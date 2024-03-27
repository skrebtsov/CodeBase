#!/bin/bash

find . -name \*.[hc] -exec sed -i 's/\x1a//g' {} \;
find . -name \*.[hc] -exec dos2unix {} \;
find . -name \*.[hc] -exec iconv -f cp866 {} -o {}.utf8 \;
find . -name \*.[hc] -exec mv -f {}.utf8 {} \; -print

exit 0
