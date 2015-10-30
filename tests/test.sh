#!/usr/bin/env bash

echo "All of the following tests should fail."
for i in fail* ; do ../parser $i ;  done 1> /dev/null
echo '=== EOF ==='

echo
echo "Following test runs ../parser pass.j and compares the output using diff."
echo "In the left column there is a reference and in the right is the actual output."
../parser pass.j > pass.out

echo
diff -y --suppress-common-lines pass.ref pass.out
