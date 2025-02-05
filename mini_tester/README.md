Minishell Test Runner

This repository contains a test runner used to compare the output of the minishell implementation with Bash. It is designed to automatically run a series of tests to ensure that the minishell behaves correctly in various scenarios.

Project Structure
    /minishell/ – Contains the minishell project source code (not part of the test runner).
    /minishell/mini_tester/ – Contains the test runner script and the test files.
        /minishell/mini_tester/runner.sh – The test runner script to execute the tests.
        /minishell/mini_tester/tests/ – Directory containing the test scripts for minishell.

Setup

    Compile your minishell executable:

    cd ../minishell  # Navigate to the minishell directory
    make            # Compile the minishell executable

    Place the test files in the /minishell/mini_tester/tests/ directory. Test scripts should have a .sh extension.

Running the Tests

To run all the tests from the /minishell/mini_tester/ folder, use:

    ./runner.sh full


Run a Specific Test (replace test_name by actual file name) :

    ./runner.sh test_name


To view detailed output for each test, use the detail option:

    ./runner.sh full detail

    or

    ./runner.sh test_name detail
