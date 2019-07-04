

main:mysql.cc
	gcc  -g  $^  -o $@ `mysql_config --cflags --libs`

.PHONE:clean
	clean:
	-rm -i main     
