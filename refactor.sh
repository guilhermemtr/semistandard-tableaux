for f in $(grep -lIR $1 *)
do
sed -i '' -e 's/$1/$2/g' $f
done
