#!/bin/sh
for file in ${*} 
do
    ex ${file} << EOF
%s/\t/        /g
wq
EOF
    echo ${file}
done
