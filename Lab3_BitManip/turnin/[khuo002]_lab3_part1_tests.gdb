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
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n
#Testing 0 case
test "PINA: 0x00 && PINB: 0x00 => PORTC: 0x00"
setPINA 0x00
setPINB 0x00
continue 5
expectPORTC 0x00
checkResult

#Testing counting only from PINA
test "PINA: 0x04 && PINB: 0x00 => PORTC: 0x01"
setPINA 0x04
setPINB 0x00
continue 5
expectPORTC 0x01
checkResult

#Testing counting only from PINB
PINA:0x00 && PINB: 0x05 => PORTC: 0x02"
setPINA 0x00
setPINB 0x05
continue 5
expectPORTC 0x02
checkResult

#Testing countin from both Pins as well as different bits
test "PINA: 0xF0 && PINB: 0x02 => PORTC: 0x05"
setPINA 0xF0
setPINB 0x02
continue 5
expectPORTC 0x05
checkResult

#Testing counting 10+ bit case.
test "PINA: 0xF0 && PINB: 0x3F => PORTC: 0x0A"
setPINA 0xF0
setPINB 0x3F
continue 5
expectPORTC 0x0A
checkResult

#Testing edge case of all 1's
test "PINA: 0xFF && PINB: 0xFF => PORTC: 0x16"
setPINA 0xFF
setPINB 0xFF
continue 5
expectPORTC 0x10
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
