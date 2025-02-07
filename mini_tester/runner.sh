#!/bin/bash

TEST_DIR="./tests"
MINISHELL="../minishell"
BASH="/bin/bash"
DETAIL_MODE=false

# Enable detailed output if the second argument is "detail"
if [ "$2" == "detail" ]; then
    DETAIL_MODE=true
fi

run_test() {
    local test_file="$1"
    local all_passed=true
    local failed_cases=""
    
    if $DETAIL_MODE; then
        echo "Running $test_file..."
    fi

    while IFS= read -r cmd || [ -n "$cmd" ]; do
	# Skip empty lines
        [ -z "$cmd" ] && continue

	# Skip comments
	[[ "$cmd" =~ ^# ]] && continue

        OUTPUT_MINISHELL=$(echo "$cmd" | $MINISHELL 2>&1)
        OUTPUT_BASH=$(echo "$cmd" | $BASH 2>&1)

        if ! diff <(echo "$OUTPUT_MINISHELL") <(echo "$OUTPUT_BASH") > /dev/null; then
            all_passed=false
            failed_cases+="\n❌ Command: '$cmd'\n------ Minishell Output ------\n$OUTPUT_MINISHELL\n------ Bash Output ------\n$OUTPUT_BASH\n"
        fi

        if $DETAIL_MODE; then
            echo -e "💻 Command: $cmd"
            echo -e "🔹 Minishell: $OUTPUT_MINISHELL"
            echo -e "🔹 Bash:      $OUTPUT_BASH"
            echo "---------------------------------"
        fi
    done < "$test_file"

    if $all_passed; then
        echo "✅ $test_file: PASS"
    else
        echo -e "❌ $test_file: FAIL $failed_cases"
    fi
    echo
}

# Run individual test if specified
if [ "$1" == "full" ]; then
    for test in $TEST_DIR/*.sh; do
        run_test "$test"
    done
elif [ -f "$TEST_DIR/$1.sh" ]; then
    run_test "$TEST_DIR/$1.sh"
else
    echo "Usage: ./test_minishell.sh full [detail] or ./test_minishell.sh <test_name>"
    exit 1
fi
