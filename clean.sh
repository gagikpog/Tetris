filenames=$(find . -name "*.cpp")

for i in $filenames
do
	temp=${i%/*}
	a=${i:$((1 + ${#temp}))}

	len=$((${#a}-3))
	fileCDate=$(stat -c%y ${i:2})
	fileODate=$(stat -c%y bin/${a:0:$(($len))}'o')
	
	[[ -z  $fileODate  ]] && continue

	fc=${fileCDate:0:$((${#fileCDate} - 16))}
	fo=${fileODate:0:$((${#fileODate} - 16))}
	
	fileC=$(date -d "$fc" +%s)
	fileO=$(date -d "$fo" +%s)

	if [ $fileC -ge $fileO ];
	then
		echo remove ${a:0:$len}'o'
		f="*${a:0:$len}o"
		find . -name $f -delete
	fi

done