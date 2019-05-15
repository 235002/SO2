#Usunąć pilki, które mają na nońcu "~", które zostały utworzone 0-2 min temu,
#głębokość do 2, znaleźć pliki "*.exe", które mają prawo wykonywania, pełna
#ścieżka kanoniczna zamienić / na \, wyświetlić 5 pierwszych

find . -type f -name "*.~" -mmin -2 -delete

find . -maxdepth 10 -name "*.exe" -perm -100 | head -5 | while read file
do
	echo `realpath $file` | tr '/' '\\'
done
