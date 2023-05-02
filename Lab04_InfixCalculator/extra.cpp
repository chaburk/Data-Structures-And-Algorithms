// MyStack<std::string> stack;
//         for (MyVector<std::string>::iterator itr = infix_tokens.begin(); itr != infix_tokens.end(); ++itr)
//         {
//             std::string s = *itr;
//             if(s == "("){
//                 stack.push("(");
//             }
//             else if(s == ")"){
//                 while (stack.top() != "(" && !stack.empty())
//                     {
//                         postfix_tokens.push_back(stack.top());
//                         stack.pop();
//                     }
//                 if(!stack.empty() && (stack.top() == "(")){
//                     stack.pop();
//                 }
//             }
//             else if ( s == "-" || s == "+" || s == "*" || s == "/")
//             {
//                 char* c = const_cast<char*>(s.c_str());
//                 char* top = const_cast<char*>(stack.top().c_str());
//                 if(stack.empty()){
//                     stack.push(s);
//                 }
//                 else{
//                     //never not empty??
//                     while((operatorPrec(*c) >= operatorPrec(*top)))
//                     {
//                         postfix_tokens.push_back(stack.top());
//                         stack.pop();
//                     }
//                     stack.push(s);
//                 }
//             }
//             else{
//                 postfix_tokens.push_back(s);
//             }
//             while(!stack.empty()){
//                 postfix_tokens.push_back(stack.top());
//                 stack.pop();
//             }


        // double ongoing = 0.0;
        // MyStack<std::string> stack;
        // for(MyVector<std::string>::iterator itr = postfix_tokens.begin(); postfix_tokens.end(); itr++){
        //     std::string s = *itr;
        //     char* c = const_cast<char*>(s.c_str());
        //     if(isDigit(*c)){
        //         stack.push(s);
        //     }
        //     else {
        //         string n1 = stack.top();
        //         stack.pop();
        //         string n2 = stack.top();
        //         stack.pop();
        //         stack.push()
        //         ongoing += computeBinaryOperation(n1, n2, s);
        //     }
        // }


// if(isDigit(token[0])){
//                 std::cout << "this is what i am pushing in digit: " << token << std::endl;
//                 std::cout << std::endl;
//                 postfix_tokens.push_back(token);
//             }
//             else if(token[0] == '-' && isDigit(token[1]) && (token.length() > 1)){
//                 std::cout << "this is what i am pushing in digit negative num: " << token << std::endl;
//                 std::cout << std::endl;
//                 postfix_tokens.push_back(token);
//             }
//             else if(isValidParenthesis(token[0])){
//                 if(token[0] == '('){
//                     std::cout << "this is top of stack in (: " << stack.top() << std::endl;
//                     std::cout << std::endl;
//                     stack.push(token);
//                 }
//                 else{
//                     while(!stack.empty() && stack.top() != "("){
//                         std::cout << "this is top of stack in ): " << stack.top() << std::endl;
//                         std::cout << std::endl;
//                         postfix_tokens.push_back(stack.top());
//                         stack.pop();
//                     }
//                     stack.pop();
//                 }
//             }
//             else {
//                 std::cout << "this is top of stack in operator: " << stack.top() << std::endl;
//                 std::cout << std::endl;
//                 std::string str = stack.top();
//                 char* c = const_cast<char*>(str.c_str());
//                 while(!stack.empty() && (operatorPrec(*c) <= operatorPrec(token[0])) && stack.top() != "("){
//                     std::cout << "this is what is being pushed to in while loop operator " << stack.top() << std::endl;
//                     postfix_tokens.push_back(stack.top());
//                     stack.pop();
//                 }
//                 stack.push(token);
//                 std::cout << std::endl;
//             }
//         }
//         while(!stack.empty()){
//             postfix_tokens.push_back(stack.top());
//             stack.pop();
//         }
//         std::cout << "loop completed - top of stack: " << stack.top() << std::endl;
//         std::cout << std::endl;