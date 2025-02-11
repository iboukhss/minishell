echo env | grep "USER"
cat | cat | ls
echo "hello world" | wc -l
printf "Line 1\nLine 2\nLine 3\n" | wc -l
echo "Home directory: $HOME" | grep "Home directory"
env | grep "PATH"
bash -c "echo 'Hello from subshell'" | grep 'Hello'
env | sort | grep -v SHLVL | grep -v ^_
cat ./test_files/infile_big | grep oi
cat minishell.h | grep ");"$
export GHOST=123 | env | grep GHOST
