#!/bin/bash

PIPEX=./pipex
OUT=outfile
HEREDOC_OUT=outfile_heredoc
LIMITER=EOF

compare_output(){
	diff "$1" "$2" > /dev/null
	if [ $? -eq 0 ]; then
		echo "✅ $3: PASS"
	else
		echo "❌ $3: FAIL"
		echo "Expected vs Your: "
		diff "$1" "$2"
	fi
	rm -rf "$1" "$2"
}

# command test
echo "<<<<<<<<<<<<<<< command test >>>>>>>>>>>>>>>"
## 0
echo "hello world" > infile
$PIPEX infile "ls -l" "wc -l" $OUT
if diff "$OUT" <(< infile ls -l | wc -l); then
	echo "✅ Test0: nomal test {ls -l | wc -l}: PASS"
else
	echo "❌ Test0: nomal test {ls -l | wc -l}: FAIL"
fi
rm -f infile $OUT

## 1
echo "Hello world" > infile
$PIPEX infile "cat" "wc -w" $OUT
< infile cat | wc -w > expected
compare_output "$OUT" expected "Test1: nomal test {cat | wc -w}"

## 2
echo -e "apple\nbanana\norange" > infile
$PIPEX infile "grep a" "tr a A" $OUT
< infile grep a | tr a A > expected
compare_output "$OUT" expected "Test2: nomal test {grep | tr}"

## 3
$PIPEX infile "noexistcommand" "wc" $OUT 2> err.txt
grep -q "command not found" err.txt && echo "✅ Test3: invalid command {noexistcommand | wc}: PASS" || echo "❌ Test3: invalid command {noexistcommand | wc}: FAIL"
rm -f err.txt "$OUT"

## 4
$PIPEX infile "wc" "noexistcommand" $OUT 2> err.txt
grep -q "command not found" err.txt && echo "✅ Test4: invalid command {wc | noexistcommand}: PASS" || echo "❌ Test4: invalid command {wc | noexistcommand}: FAIL"
rm -f err.txt $OUT

## 5
echo "echo forbidden" > forbidden.sh
chmod -x forbidden.sh
$PIPEX infile "./forbidden.sh" "wc" $OUT 2> err.txt
grep -q "Permission denied" err.txt && echo "✅ Test5: permission denied {./forbidden.sh | wc}: PASS" || echo "❌ Test5: permission denied {./forbidden.sh | wc}: FAIL"
rm -f err.txt "$OUT" forbidden.sh

## 6
echo -e "a\nb\nc" > infile
$PIPEX infile "cat" "tr a-z A-Z" "rev" "wc -c" $OUT
< infile cat | tr a-z A-Z | rev | wc -c > expected
compare_output "$OUT" expected "Test6: multiple commands {cat | tr a-z A-Z | rev | wc -c}:"

## 7
echo -e "apple\nbanana\ncherry\ndate\nelderberry\nfig\ngrape\napple\nbanana" > infile
$PIPEX infile "cat" "tr a-z A-Z" "sort" "uniq" "rev" "tr A-Z a-z" "grep -v a" "tr e E" "cut -c1-5" "wc -l" $OUT
< infile cat | tr a-z A-Z | sort | uniq | rev | tr A-Z a-z | grep -v a | tr e E | cut -c1-5 | wc -l > expected
compare_output "$OUT" expected "Test7: 10 command {cat | tr a-z A-Z | sort | uniq | rev | tr A-Z a-z | grep -v a | tr e E | cut -c1-5 | wc -l}: "

## 8
echo -e "hello world" > infile
$PIPEX infile "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" \
"cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" $OUT
< infile cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat |\
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat  > expected
compare_output "$OUT" expected "Test8: 100 commands {cat | cat ... | cat}: "

## 9 
echo "hello world\nhello c\nhello 42\nhello tokyo\n" > infile
$PIPEX infile "cat" "grep \"hello world\"" $OUT
< infile cat | grep "hello world" > expected
compare_output "$OUT" expected "Test9: space split{cat | grep \"hello world\"}: "

# file test
echo "<<<<<<<<<<<<<<< file test >>>>>>>>>>>>>>>"
## 0
echo "hello world" > infile
$PIPEX infile "cat" "cat" $OUT
< infile cat | cat > expected
compare_output "$OUT" expected "Test0: redirect normal test {cat | cat}: "

## 1
yes "0123456789" | tr -d '\n' | head -c 6000 > infile
$PIPEX infile "cat" "cat" $OUT
< infile cat | cat > expected
compare_output "$OUT" expected "Test1: redirect biginput test { cat | cat }: "

##  2
echo "hello world" > infile
chmod -r infile
$PIPEX infile "cat" "cat" $OUT 2> err.txt
grep -q "Permission denied" err.txt && echo "✅ Test2: input file permission denied: PASS" || echo "❌ Test2: input file permission denied: FAIL"
rm -f err.txt infile $OUT

## 3
echo "hello world" > infile
touch $OUT
chmod 000 $OUT
$PIPEX infile "cat" "cat" $OUT 2>err.txt
grep -q "Permission denied" err.txt && echo "✅ Test3: output file permission denied: PASS" || echo "❌ Test3: output file  permission denied: FAIL"
rm -f err.txt infile $OUT

$PIPEX noexistfile "cat" "cat" $OUT 2>err.txt
grep -q "No such file or directory" err.txt && echo "✅ Test4: non exist file: PASS" || echo "❌ Test4: non exist file: PASS"
rm -f err.txt
