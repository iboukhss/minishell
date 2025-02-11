/bin/ls
/bin/ls -l
/bin/pwd
exit 1234
exit hello 1234
exit hello1234
/bin/ls -l | wc -l
/bin/ls | grep "some_file"
/bin/ls /bin | grep "ls"
/bin/ls -la | grep "\.bashrc"
/bin/echo "Hello, world!" | grep "Hello"
/bin/echo "Minishell test" > testfile.txt
/bin/cat testfile.txt | grep "Minishell"
/bin/echo "hello minishell" | /bin/grep "minishell"
/bin/echo "word1 word2 word3" | /bin/wc -w
/bin/ls /bin | /bin/wc -l


