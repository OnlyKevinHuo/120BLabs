# Test file for Lab3_BitManip


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#      printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

#Testing 0 case and Seatbelt
test "PINA: 0x30=> PORTC: 0x40"
setPINA 0x70
continue 5
expectPORTC 0xC0
checkResult

#Testing Low Gas and Seatbelt
test "PINA:0x74 => PORTC: 0xEE"
setPINA 0x74
continue 5
expectPORTC 0xF0
checkResult

#Testing 5-6 and Seatbelt
test "PINA: 0x76=> PORTC: 0xB8"
setPINA 0x76
continue 5
expectPORTC 0xB8
checkResult

#Testing Full Gas and Seatbelt
test "PINA: 0x7F=> PORTC: 0xEF"
setPINA 0x7F
continue 5
expectPORTC 0xBF
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
