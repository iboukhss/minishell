echo env | grep "USER"
cat | cat | ls
echo "hello world" | wc -l
printf "Line 1\nLine 2\nLine 3\n" | wc -l
echo "Home directory: $HOME" | grep "Home directory"
env | grep "PATH"
echo $(echo "hello world") | wc -w
bash -c "echo 'Hello from subshell'" | grep 'Hello'
