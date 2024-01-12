#include<future>

/*
    alt + Z
    A   B   C

    Option 1: one after the other. ====> single thread technique
    ////////////////////////////////////////////////////////////////
    Option 2: I will complete all tasks in such a way that I "practically start all of them at the same time" but keep juggling them based on some criteria. ================> multi-thread approach
    /////////////////////////////////////////////////////////////
    Option 3: map number of tasks among number of available "workers". =============> Parallel approach
    //////////////////////////////////////////////////////////////
    Option 4: Start a task. delegate it to another worker OR do it yourself after some time.

    If someone else is doing a task, monitor it,wait for their work to be done,take follow-up actions accordingly.
    ==========> asynchronous execution

*/

/*
    2 tasks
    Calculate factorial of 5
    Calculate square of a number given by the user.


*/
#include<iostream>


int square(std::future<int>& ft)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"hello from square I have started my work! \n";
    int number = ft.get();
    return number *number;
}

int factorial(int number){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if(number<0){
        throw std::runtime_error("negative number error!");
    }
    if(number ==0 || number ==1){
        return 1;
    }
    else{
        return number * factorial(number-1);
    }
}

int main()
{
    // step 1: make a promise 
    std::promise<int>pr;

    // step 2: A future linked to the promise
    std::future<int>ft = pr.get_future();

    /*

     OS: launch square(if possible as a new thread)

    */
    std::future<int>result_ft=std::async(std::launch::async,&square,std::ref(ft));

    std::cout<< factorial(5);
    int val=0;
    std::cin>>val;
    pr.set_value(val);
    std::cout<<"result of the square is"<<result_ft.get()<<"\n";
}

/*
    client-server architecture 

    future-promise model

    square calculation 

    Main needs to delegate the task of square calculation

    ------------> A new thread for square will be registered with OS 





*/