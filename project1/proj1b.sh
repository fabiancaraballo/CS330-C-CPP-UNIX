#!/bin/bash

mkdir rootdir
cd rootdir
mkdir dir1
mkdir dir2
cd dir1 
touch file1
chmod 400 file1
mkdir dir3
chmod 777 dir3
cd dir3
mkdir dir4
chmod 750 dir4
cd dir4
touch file4
touch file3 
chmod 666 file4
chmod 200 file3
cd ../../
chmod 000 dir3
cd ../ 
chmod 775 dir2
cd dir2
touch file2
chmod 640 file2


