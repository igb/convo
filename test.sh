
if [ `./convo --dec 10` ]
then
    echo "PASS executable working." 
fi


input="test_cases.csv"

while IFS= read -r line
do
    bin_val=` echo "$line" | awk -F',' '{print $1}'`
    dec_val=` echo "$line" | awk -F',' '{print $2}'`
    converted_val=`./convo $bin_val`

    if [ "$converted_val" == "$dec_val" ]; then
	echo "PASS $bin_val == $dec_val"
    else
	echo "FAIL expected $bin_val to equal $dec_val but got $converted_val"
    fi
    
done < "$input"

