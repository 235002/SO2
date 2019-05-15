cd ./Test/test1
for i in {1..7}
do
	touch test$i.txt
	echo "test$i: test$i" > test$i.txt
	chmod 024 test$1.txt
done
