#! /bin/python3

import os.path
import random
import string
import sys


if(len(sys.argv) <= 2 or len(sys.argv) > 3):
	print("Usage ./generate_tests.py [folder] [count of tests]")
	exit(0)


TARGET_FOLDER	= sys.argv[1]
COUNT_OF_TESTS	= int(sys.argv[2])
JS_MARK		= "<script>evil_script()</script>"
MACOS_MARK	= "system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")"
UNIX_MARK	= "rm -rf ~/Documents"


def random_string(length: int) -> str:
	return ''.join([random.choice(string.ascii_lowercase) for i in range(length)])


def generate_text(number: int, length: int, mark: str="") -> None:
	fish_text = random_string(length // 2) + mark + random_string(length // 2)
	extension = random_string(10) + ".js" if mark == JS_MARK else "." + random_string(5)
	with open(os.path.join(TARGET_FOLDER, "test_number" + str(number)) + extension, "w") as test_file:
		test_file.write(fish_text)
	return None


if __name__ == "__main__":

	TOTAL = 0
	JS_RES = 0
	MACOS_RES = 0
	UNIX_RES = 0

	for current_test_number in range(COUNT_OF_TESTS):
		FLAG = random.randint(0,4)
		TOTAL += 1
		if(FLAG == 0 or FLAG == 4):
			generate_text(current_test_number, random.randint(500, 100000))
		elif(FLAG == 1):
			JS_RES += 1
			generate_text(current_test_number, random.randint(500, 100000), JS_MARK)
		elif(FLAG == 2):
			UNIX_RES += 1
			generate_text(current_test_number, random.randint(500, 100000), UNIX_MARK)
		else:
			MACOS_RES += 1
			generate_text(current_test_number, random.randint(500, 100000), MACOS_MARK)
	with open("true_results.txt", "w") as results_file:
		results_file.write("====== True result ======\n")
		results_file.write(f"Processed files: %d\n" % TOTAL)
		results_file.write(f"JS detects: %d\n" % JS_RES)
		results_file.write(f"Unix detects: %d\n" % UNIX_RES)
		results_file.write(f"macOS detects: %d\n" % MACOS_RES)
		results_file.write("Errors: 0\n")
		results_file.write("=" * 25 + "\n")
