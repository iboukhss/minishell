echo hello world
echo "hello world"
echo -n "hello world"
echo 123Hello $USER
echo '$USER' "$USER"
echo $? 
echo $? + $?
echo "cat lol.c | cat > lol.c"
echo "          lol           " 'this is a test      !'
echo "mix 'quotes to see' what happens" '  hello "$USER" how it goes'
echo "mix ' $PWD ' what happens" '  hello "$USER" how it goes'
echo $
echo $ $

#Case that Bash is returning an integer while minishell is printing $$
#echo $$