#!/usr/bin/env bash

echo "All of the following tests should fail with bad lexemes msg:"
for i in fail* ; do ../parser $i ;  done 1> /dev/null

echo
echo "Following test runs ../parser pass.j and compares the output using diff:"
../parser pass.j > pass.out

echo
diff -y pass.j pass.out
