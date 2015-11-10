#!/usr/bin/env bash

__RAINBOWPALETTE="1"
function __colortext()
{
  echo -e " \e[$__RAINBOWPALETTE;$2m$1\e[0m"
}

function pass()
{
  echo -n $(__colortext "PASS\t" "32")
  echo "$@"
}

function fail()
{
  echo -n $(__colortext "FAIL\t" "31")
  echo "$@"
}


for i in fail*.json ;
do
    ../parser "$i"
    if [[ "$?" != 0 ]]
    then
        pass "$i"
    else
        fail "$i"
        exit 1
    fi
done

NOFILE=nofile.json
../parser $NOFILE
if [[ "$?" == 1 ]]
then
    pass $NOFILE
else
    fail $NOFILE
    exit 1
fi

# test reference config
REF=pass-reference.json
../parser $REF
if [[ "$?" == 0 ]]
then
    pass $REF
else
    fail $REF
    exit 1
fi

res="$(../parser pass.json | diff -y pass.ref -)"

if [[ "$?" == 0 ]]
then
    pass "pass.json"
else
    fail "pass.json      see ./tests/pass.diff"
    echo "$res" > pass.diff
    exit 1
fi
