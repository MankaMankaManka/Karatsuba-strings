#include <iostream>
#include <string>

std::string addStrings(std::string num1, std::string num2, int base) {
    int maxLength = std::max(num1.size(), num2.size());
    int carry = 0;
    int sum;
    std::string result;

    // make strings same length with 0s padding front
    while (num1.size() < maxLength){
        num1.insert(0, "0");
    }
    
    while (num2.size() < maxLength){
        num2.insert(0, "0");
    }
    
    // add from end of strings to start
    for (int i = maxLength - 1; i >= 0; i--) {
        sum = (num1[i] - '0') + (num2[i] - '0') + carry;
        carry = sum / base;
        result.insert(0, std::to_string(sum % base));
    }

    // Add any remaining carry
    if (carry==1){
        result.insert(0, std::to_string(carry));
    }
    // Remove leading zeros
    return result.erase(0, std::min(result.find_first_not_of('0'), result.size() - 1));
}

std::string subtractStrings(std::string num1, std::string num2, int base) {
    int maxLength = std::max(num1.size(), num2.size());
    int diff;
    std::string result;

    // Ensure both numbers have the same length
    while (num1.size() < maxLength)
        num1.insert(0, "0");

    while (num2.size() < maxLength)
        num2.insert(0, "0");

    // Perform subtraction from right to left
    for (int i = maxLength - 1; i >= 0; i--) {
        diff = (num1[i] - '0') - (num2[i] - '0');
        if (diff >= 0)
            result.insert(0, std::to_string(diff));
        else {
            // Borrow from the previous column
            int j = i - 1;
            while (j >= 0) {
                num1[j] = ((num1[j] - '0') - 1) % base + '0';
                char maxincol = base-1 +'0';
                
                if (num1[j] != maxincol){
                    break;
                }
                else{
                    j--;
                }
            }
            result.insert(0, std::to_string(diff + base));
        }
    }

    // Remove leading zeros
    return result.erase(0, std::min(result.find_first_not_of('0'), result.size() - 1));
}

std::string multiplyStrings(std::string num1, std::string num2, int base) {
    int maxLength = std::max(num1.size(), num2.size());

    // Ensure both numbers have the same length
    while (num1.size() < maxLength)
        num1.insert(0, "0");

    while (num2.size() < maxLength)
        num2.insert(0, "0");

    // Base case: if the length is 1, perform simple multiplication
    if (maxLength == 1){
        int product= (num1[0] - '0') * (num2[0] - '0');
        std::string stringproduct="";
        while(product>0){
            stringproduct = std::to_string(product%base) + stringproduct;
            product/=base;
        }
        return stringproduct;
    }

    // Split the numbers into halves
    std::string num1Left = num1.substr(0, maxLength / 2);
    std::string num1Right = num1.substr(maxLength / 2, maxLength - maxLength / 2);
    std::string num2Left = num2.substr(0, maxLength / 2);
    std::string num2Right = num2.substr(maxLength / 2, maxLength - maxLength / 2);

    // Recursive multiplication
    std::string p0 = multiplyStrings(num1Left, num2Left, base);
    std::string p1 = multiplyStrings(num1Right, num2Right, base);
    std::string p2 = multiplyStrings(addStrings(num1Left, num1Right, base), addStrings(num2Left, num2Right, base), base);
    std::string p3 = subtractStrings(p2, addStrings(p0, p1, base), base);

    // Combine the results with appropriate zeros
    for (int i = 0; i < 2 * (maxLength - maxLength / 2); i++)
        p0.append("0");
    for (int i = 0; i < maxLength - maxLength / 2; i++)
        p3.append("0");

    // Sum the parts to get the final result
    return addStrings(addStrings(p0, p1, base), p3, base);
}

int main() {
    std::string I1, I2;
    int B;
    std::cin >> I1 >> I2 >> B;
    std::cout << addStrings(I1, I2, B) <<" ";
    std::cout << subtractStrings(I1, I2, B)<< " ";
    std::cout << multiplyStrings(I1, I2, B) <<" 0";
    return 0;
    //50172018014163055421063080735405412450321060708 50172018014163055421063080735405412450321060708 9
}//2720054313400647131221703727161535751530336803030108876216430554402184801340712126433372723471
//
