env | grep -v "_"
export SCHOOL=42
export PROJECT=minishell SCORE=100
echo "Welcome at $SCHOOL. You passed the project $PROJECT with a score of $SCORE"
unset SCHOOL
echo "Welcome at $SCHOOL. You passed the project $PROJECT with a score of $SCORE"
unset PROJECT SCORE
echo "Welcome at $SCHOOL. You passed the project $PROJECT with a score of $SCORE"