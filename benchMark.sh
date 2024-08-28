
echo "abracadabra"
hyperfine -N "./compress_c" "./compress_rust"
echo "1 paragrapoh"
hyperfine -N "./compress_c ./files_test/test1" "./compress_rust ./files_test/test1"

echo "5 paragrapoh"
hyperfine -N "./compress_c ./files_test/test2" "./compress_rust ./files_test/test2"
echo "mega test"
hyperfine -N "./compress_c ./files_test/test" "./compress_rust ./files_test/test"