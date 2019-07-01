# Test file for LabFOUR


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

#testing Adding 1
test "PINA: 0x00, 0x01 => PORTC: 0x08, state: Calc_Wait"
setPINA 0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 5
expectPORTC 0x08
expect Calc_State Calc_Init
checkResult

#Testing Subtracting 1 and Returning to Init
test "PINA: 0x00, 0x02 => PORTC: 0x06, state: Calc_Init"
setPINA 0x00
continue 3
setPINA 0x02
continue 3
setPINA 0x00
continue 3
setPINA 0x02
continue 3
setPINA 0x00
continue 3
setPINA 0x02
continue 3
expectPORTC 0x06
expect Calc_State Calc_Wait
checkResult


#Testing Adding 1 then Subtracting 2
test "PINA: 0x00, 0x01, 0x00, 0x02(x2), 0x00 => PORTC: 0x06, state: Calc_Init"
setPINA 0x00
continue 3
setPINA 0x01
continue 3
setPINA 0x00
continue 2
setPINA 0x02
continue 3
setPINA 0x00
continue 4
setPINA 0x02
continue 3
setPINA 0x00
continue 6
setPINA 0x02
continue 3
setPINA 0x00
continue 6


expectPORTC 0x05
expect Calc_State Calc_Init
checkResult

#Testing Adding up to 9;
test "PINA: 0x00, 0x01(x3) => PORTC: 0x01, state: LED_S1"
setPINA 0x00
continue 3
setPINA 0x01
continue 3
setPINA 0x00
continue 3
setPINA 0x01
continue 3
setPINA 0x00
continue 3
setPINA 0x01
continue 3
setPINA 0x00
continue 3
setPINA 0x01
continue 3

expectPORTC 0x09
expect Calc_State Calc_Init
checkResult

#Testing Reset from Init
test "PINA: 0x03 => PORTC: 0x00, state: Calc_Wait"
setPINA 0x00
continue 4
expectPORTC 0x00
expect Calc_State Calc_Init
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
