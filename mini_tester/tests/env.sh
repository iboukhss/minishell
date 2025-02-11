env | grep -v "_"
export SCHOOL=42
export PROJECT=minishell SCORE=100
echo "welcome at $SCHOOL. You passed the project $PROJECT with a score of $SCORE"
unset SCHOOL
echo "welcome at $SCHOOL. You passed the project $PROJECT with a score of $SCORE"
unset PROJECT SCORE
