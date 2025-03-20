 #include<iostream>
#include<vector>
#include <iomanip>

class Date
{
	private:
		int month;
		int day;
		int year;
	public:
		Date(int month,int day,int year)
		{
			this->month=month;
			this->day=day;
			this->year=year;
		}
		
		std::string displayDate()
		{
			return std::to_string(month)+"/"+std::to_string(day)+"/"+std::to_string(year);
		}
};//end date class

class Hotel
{
	private:
		std::string hotelName;
		double nightlyCost;
	public:
		Hotel()
		{
			
		}
		
		Hotel(std::string hotelName,double nightlyCost)
		{
			this->hotelName=hotelName;
			this->nightlyCost=nightlyCost;
		}
		
		std::string displayHotel()
		{
			return "\n$"+std::to_string(nightlyCost)+" (per night)"+hotelName;
		}
		double getNightlyCost(){return nightlyCost;}
};//end hotel class

class Attraction
{
	private:
		std::string attraname;
		double ticketCost;
	public:
		Attraction(std::string attraname,double ticketCost)
		{
			this->attraname=attraname;
			this->ticketCost=ticketCost;
		}
		void displayAttraction()
		{
			std::cout<<"\n$ "<<std::setw(8)<<ticketCost<<" "<<attraname;
		}
		
		double getTicketCost(){return ticketCost;}
}; //end attraction

class Trip
{
	private:
		Date startingDate;
		Date endingDate;
		std::string destinationName;
		Hotel chosenHotel;
		std::vector<Attraction>chosenAttraction;
		double totalCost;
		int numPpl;
		
		public:
			Trip(int sm,int sd, int sy, int em, int ed, int ey,std::string destinationName,int people) : startingDate(sm,sd,sy), endingDate(em,ed,ey)
			{
				this->destinationName=destinationName;
				this->numPpl=people;
			}
			
			void setChosenHotel(Hotel cs){chosenHotel=cs;}
			
			void addAttraction(Attraction oneAttraction) 
			{
				chosenAttraction.push_back(oneAttraction);
			}
			
			void calculateCost() 
			{
				totalCost = chosenHotel.getNightlyCost() *5;
				for(auto oneAttraction:chosenAttraction )
				{
					totalCost +=oneAttraction.getTicketCost() * numPpl;
				}
			}
			
			void displayTrip() 
			{
				std::cout<<"\nYour trip to "<<destinationName<<" for"<<numPpl<<" people: ";
				std::cout<<"\nDate Leaving	"<<startingDate.displayDate();
				std::cout<<"\nDate Returning  "<<endingDate.displayDate();
				std::cout<<"\nStaying at: "<<chosenHotel.displayHotel();
				std::cout<<"\nSelected Attractions ";
				for(auto oneAttraction :chosenAttraction)
				{
					oneAttraction.displayAttraction();
				}
				std::cout<<"\n\nTotal cost of trip:  $ "<<totalCost;
			}
};//endclasstrip
std::string selectDestination();
Hotel selectHotel();
void selectAttractions(Trip& myTrip);
int main()
{ 
	int am, ad, ay, dm, dd, dy, people;

    std::cout<<std::setprecision(2)<<std::fixed;

    std::string destination = selectDestination();

    std::cout<<"\nEnter date of arrival to "<<destination<<": MM DD YYYY ";
    std::cin>>am>>ad>>ay;

    std::cout<<"\nEnter date of departure from "<<destination<<": MM DD YYYY ";
    std::cin>>dm>>dd>>dy;

    std::cout<<"\nHow many people are going on the trip? ";
    std::cin>>people;

   Trip myTrip(am,ad,ay,dm,dd,dy,destination, people);

   Hotel selectedHotel = selectHotel();

   myTrip.setChosenHotel(selectedHotel);

   selectAttractions(myTrip);

   myTrip.calculateCost();
   myTrip.displayTrip();

	
	
	
	
return 0;
}

std::string selectDestination() 
{
	std::string chosenCity;
	std::vector <std::string> destinationCities {"Mackinaw Island", "Holland", "Traverse City", "Houghton"};
	
	std::cout<<"\nPlease choose a city: ";
	
	for(auto city :destinationCities)
	{
		std::cout<<"\n\t"<<city;
	}
	std::cout<<"-------> ";
	getline(std::cin,chosenCity);
	
	return chosenCity;
}
Hotel selectHotel() 
{
	Hotel allHotels[4] = { Hotel("Hilton Garden Inn",164),
 Hotel("Quality Inn and Suites",105),
 Hotel("Holiday Inn",139),
 Hotel("Marriott", 152)
                         };
                         
    int x,choice;
    std::cout<<"\nChoose a hotel: \n";

    for (auto cs: allHotels)
    {
    	 std::cout<<x<<": "<<cs.displayHotel()<<std::endl;
         x++;
	}
	     std::cout<<"\n------------> ";

	std::cin>>choice;
	
	while(choice <1 ||choice>4||std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(10,'\n');
		std::cout<<"\nINVALID choose 1-4";
		std::cout<<"\nChoose a hotel: \n";
		std::cin>>choice;
	}
	
	return allHotels[choice-1];
}

void selectAttractions(Trip& myTrip)
{
     Attraction allAttractions[8] = {
                           Attraction("Zoo",16.50),
                           Attraction("Historical Museum",10.50),
                           Attraction("Stadium",139.00),
                           Attraction("River Boat", 152.00),
                           Attraction("Theater", 131.22),
                           Attraction("Science Center", 12.95),
                           Attraction("Art Museum", 14.50),
                           Attraction("Amusement Park", 52.75)
                        };
    char choice;
    int x , selection;

    std::cout<<"\nWould you like to add an attraction?";
    std::cin>>choice;
    while (choice == 'y')
    {   x = 1;
        for (Attraction oneAttraction : allAttractions)
        {
            std::cout<<"\n"<<x;
            oneAttraction.displayAttraction();
            x++;
        }
        std::cout<<"\nPlease make a selection --->";
        std::cin>>selection;

        myTrip.addAttraction(allAttractions[selection-1]);

        std::cout<<"\nWould you like to add another attraction?";
        std::cin>>choice;
    }
}
