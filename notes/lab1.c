int isLessOrEqual(int x, int y) {
  int x_sign = x >> 31 & 0x1;     // Get the sign bit of x
  int y_sign = y >> 31 & 0x1;     // Get the sign bit of y
  int is_x_neg_y_pos = (x_sign & ~y_sign);  // Check if x is negative and y is positive
  int is_x_pos_y_neg = (~x_sign & y_sign); // Check if x and y have the same sign
  int y_minus_x = y + (~x + 1);   // Compute y - x
  int y_minus_x_sign = y_minus_x >> 31;  // Get the sign bit of y - x
  int has_overflow = (is_x_pos_y_neg & (x_sign ^ y_minus_x_sign));  // Check for overflow
  return is_x_neg_y_pos | (!is_x_pos_y_neg & !has_overflow);  // Return 1 if x <= y, 0 otherwise
}
Here's a more detailed explanation of each line:
int x_sign = x >> 31 & 0x1;: This line gets the sign bit of x by right-shifting x by 31 bits (to shift the sign bit all the way to the right), and then masking off all but the least significant bit (using & 0x1).
int y_sign = y >> 31 & 0x1;: This line gets the sign bit of y using the same method as above.
int is_x_negative = (x_sign & ~y_sign);: This line checks if x is negative and y is positive by using bitwise AND (&) and bitwise NOT (~) operations. If x is negative (x_sign is 1) and y is not negative (y_sign is 0), then the result of ~y_sign will be all ones except for the least significant bit (which is zero). When x_sign is bitwise ANDed with this value, the result will be all zeros except for the least significant bit, which will be one.
int is_x_and_y_same_sign = (~x_sign & y_sign);: This line checks if x and y have the same sign by using bitwise NOT (~) and bitwise AND (&) operations. If x and y have the same sign, then the sign bit of x will be zero (~x_sign will be all ones except for the least significant bit), and the sign bit of y will be one (y_sign will be all zeros except for the least significant bit). When ~x_sign is bitwise ANDed with y_sign, the result will be all zeros except for the least significant bit, which will be one.
int y_minus_x = y + (~x + 1);: This line computes y - x using two's complement arithmetic. It does this by negating x (using ~x + 1) and adding it to y.

int y_minus_x_sign = y_minus_x >> 31;: This line gets the sign bit of y - x by right-shifting y_minus_x by 31 bits (to shift the sign bit all the way to the right).

int has_overflow = (is_x_and_y_same_sign & (x_sign ^ y_minus_x_sign));: This line checks for overflow by using bitwise AND (&) and bitwise XOR (^) operations. If x and y have the same sign (is_x_and_y_same_sign is 1) and the sign of y - x is different from the sign of x (x_sign ^ y_minus_x_sign is 1), then there is overflow. This is because if x and y have the same sign, then their sum or difference cannot overflow unless the result has the opposite sign. The result of this expression will be 1 if there is overflow, and 0 otherwise. 

return is_x_negative | (!is_x_and_y_same_sign & !has_overflow);: This line returns 1 if x <= y and 0 otherwise. If x is negative and y is positive (is_x_negative is 1), then x is definitely less than or equal to y. If x and y have the same sign and there is no overflow (!is_x_and_y_same_sign & !has_overflow is 1), then y - x is non-negative, so x is less than or equal to y.