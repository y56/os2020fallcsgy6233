#!/bin/bash

function check_cmd {
    command -v pkill > /dev/null || echo 'Missing pkill'
    command -v timeout > /dev/null || echo 'Missing timeout'
}

function build {
    BUILD_EC=0
    echo "[Building with 'gcc $@']"
    if ! gcc "$@" ; then
        echo '[Building failed]'
        BUILD_EC=1
    fi
}

function run {
    if [[ $BUILD_EC != 0 ]]; then
        return
    fi

    echo "[Running part a with args '$2 $3']"

    ./cs6233_consumer |tee $TEMP_DIR/out.log &
    sleep 0.1
    if ! netstat -tunpl 2> /dev/null |egrep '^.+8000.+LISTEN.*$' ; then
        echo '[Not listening 8000]'
    fi

    timeout $1 ./cs6233_producer $2 $3
    echo
    echo "[Producer return code = $?][should be 0]"

    sleep 0.1
    if pkill cs6233_consumer ; then
        echo '[Consumer not exiting][should exit]'
    fi

    RUN_RESULT=`cat $TEMP_DIR/out.log |xargs echo`
    if [[ "$RUN_RESULT" != "$EXPECTED" ]]; then
        echo '[Result does not match expected]'
        echo '[Expected output]'
        echo "$EXPECTED"
        echo '[Actual output]'
        echo "$RUN_RESULT"
    else
        echo '[Result match expected]'
    fi
}

function main {
    check_cmd

    TEMP_DIR=`mktemp -d`

    build a.consumer.c -o cs6233_consumer
    build a.producer.c -o cs6233_producer

    echo "-----------------------------"
    EXPECTED='0 5 10 15'
    run 6 4 5

    echo "-----------------------------"
    EXPECTED='0 17 34 51 68 85 102 119 136 153 170'
    run 13 11 17

    echo "-----------------------------"
    #build b.c -o cs6233_b -lrt
    #if [[ $BUILD_EC != 0 ]]; then
    #    return
    #fi
    #echo '[Running part b]'
    #./cs6233_b 5 2

    rm -r $TEMP_DIR
}

main "$@"
