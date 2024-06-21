**When the code is executed on terminal**

It will ask the identity(Manager/Employee/Customer)

**If You are Manager[Ther is only one manager] ,id = mm001,name = vishal(case sensitive),password = 123456**

The Manager is able to login only if it provides correct credentials as mentioned above.Otherwise the program will terminate.

 After login the manager can:-

 **Edit**

 **Car Record**

**Employee Record**

**Customer Record**


In Car Record he can:-

 **Add Cars**(which get added in car.csv file,assuming that the car is not rented simultaneosly while adding),

 **Display** the details of car using model number,

 **Update** the car details using previous model number[the updated results appear in car.csv as well as customer.csv/emoployee.csv file],

 **Delete** the car details using model number[the record get deleted in car.csv file and corresponding results are reflected in employee.csv and customer.csv files].


The manager can perfoem similar add/delete/upadte/search operation for customer and employee.

**NOTE:- There is one to one mapping b/w customer record and rent car limit.**

**Car_limit   #Customer/Employee Record**

     **4**            **Good**

     **3**            **average**

     **2**            **bad**

     **1**            **worst**



The customer/employee record and car_limit is updated based on the car returned by the user.


**Functions for Customer and Employee**

If a new customer comes,he has to signup first using a four character user id ex:-2cc2,A four digit password and name
Now the recors for the customer get stored in the customer database with no_of_rented_cars = 0,customer_record = average,so the rent_car_limit is 3.
After that he needs to login through same credentials he entered durig signup,otherwise function will get terminate.
After login,he can


 **showAvailable_Cars**[Cars which is not rented yet or whose **Is_Rented value = 0**,displayed using model number]

 **showCurrentlyRented_Cars**[Can view the cars he is currently renting,displayed using **model number**]

 **Show_carDuedate**[Browse using **model_number**]

 **Rent_car**[Can rent car only if the customer has feasible customer record,If he is able to rent the car he can rent the available car whose Is_Rented value = 1,On renting the car the corrsponding changes will get reflected in the **Car.csv and **Customer.csv** file]

 Return_Request[On returning the car,the customer_records and the car_rent_limit is either decreased based on the return date of the car and so the car rent limit,the cahnges get updated in the customer.csv and car.csv file].



 The similar things are done by employees with the difference that the cars to employees are shown at **15% discount**.
