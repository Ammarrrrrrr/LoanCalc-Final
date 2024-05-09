#rm -rf FakeDataGen/build
cmake FakeDataGen -B FakeDataGen/build
cd FakeDataGen/build
make -j128
mv a.out ..
cd ..
mv a.out ..
cd ..
mkdir bin
mv a.out bin
./bin/a.out   
#done genrerating data and placing it in correct dir


#start actual prog
g++ -o bin/prog LoansCalc/main.cpp
./bin/prog

mkdir out
mv loans.csv out
mv loan_order_sjf.txt out
mv loan_order_fcfs.txt out
mv loan_data_with_monthly_payment.csv out

cd out 
echo "SJF: "
cat loan_order_sjf.txt

echo "FCFS: "
cat loan_order_fcfs.txt

echo "In the current case and implemtation, using SJF or FCFS wont differ. "