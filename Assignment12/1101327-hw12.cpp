#include <iostream>
#include <iomanip>
#include <fstream>
//#include <ctime>
using namespace std;

struct Date
{
   int year;
   int month;
   int day;
};

struct Reservation
{
   char flightNo[ 8 ]; // flight number
   char id[ 12 ];      // ID number
   char name[ 8 ];     // name
   char mobile[ 12 ];  // mobile phone number
   char date[ 12 ];    // departure date
   int tickets[ 8 ];
   // tickets[ 0 ]: not used
   // tickets[ 1 ]: number of full fare tickets
   // tickets[ 2 ]: number of child tickets
   // tickets[ 3 ]: number of infant tickets
   // tickets[ 4 ]: number of senior citizen tickets
   // tickets[ 5 ]: number of impaired tickets
   // tickets[ 6 ]: number of impaired companion tickets
   // tickets[ 7 ]: number of military tickets
};

struct Flight
{
   char flightNo[ 8 ];      // flight number
   char aircraft[ 8 ];      // aircraft model
   int departureAirport;    // departure airport code
   int arrivalAirport;      // arrival airport code
   char departureTime[ 8 ]; // departure time
   char arrivalTime[ 8 ];   // arrival time
   int dayWeek[ 7 ];        // the value of dayWeek[ i ] is 0 or 1
   // dayWeek[ 0 ] == 1 if and only if the flight flies on Sunday
   // dayWeek[ 1 ] == 1 if and only if the flight flies on Monday
   // dayWeek[ 2 ] == 1 if and only if the flight flies on Tuesday
   // dayWeek[ 3 ] == 1 if and only if the flight flies on Wednesday
   // dayWeek[ 4 ] == 1 if and only if the flight flies on Thursday
   // dayWeek[ 5 ] == 1 if and only if the flight flies on Friday
   // dayWeek[ 6 ] == 1 if and only if the flight flies on Saturday
};

struct FlightSeats
{
   char date[ 12 ];      // date
   char flightNo[ 8 ];   // flight number
   int departureAirport; // departure airport code
   int arrivalAirport;   // arrival airport code
   int availableSeats;   // the number of available seats
};

const char airportName[ 12 ][ 12 ] = { "", "Taipei",    "Taichung", "Chiayi",  "Tainan",
                                         "Kaohsiung", "Hualien", "Taitung",
                                         "Penghu",    "Kinmen",   "Beigan",  "Nangan" };

// row 0 and column 0 are not used,
// fullFare[ i ][ j ] is the full fare from airport i to airport j
const int fullFare[ 12 ][ 12 ] = {
   { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0,    0,    0,    0,    0,    0, 1781, 2460, 2296, 2618, 2197, 2197 },
   { 0,    0,    0,    0,    0,    0,    0,    0, 1769, 2236,    0, 2686 },
   { 0,    0,    0,    0,    0,    0,    0,    0, 1721, 2217,    0,    0 },
   { 0,    0,    0,    0,    0,    0,    0,    0, 1697, 2231,    0,    0 },
   { 0,    0,    0,    0,    0,    0,    0,    0, 1876, 2393,    0,    0 },
   { 0, 1781,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2460,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2296, 1769, 1721, 1697, 1876,    0,    0,    0, 1768,    0,    0 },
   { 0, 2618, 2236, 2217, 2231, 2393,    0,    0, 1768,    0,    0,    0 },
   { 0, 2197,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2197, 2686,    0,    0,    0,    0,    0,    0,    0,    0,    0 } };

const int discount[ 8 ] = { 0, 100, 75, 0, 50, 50, 50, 95 };
// discount[ 0 ]: not used
// discount[ 1 ]: Full Fare Ticket (肂布)
// discount[ 2 ]: Child Ticket (ㄠ担布):                 25% off of the full fare
// discount[ 3 ]: Infant Ticket (捆ㄠ布):                Free of charge
// discount[ 4 ]: Senior Citizen Ticket (穛ρ布):        50% off of the full fare
// discount[ 5 ]: Impaired Ticket (稲み布):              50% off of the full fare
// discount[ 6 ]: Impaired Companion Ticket (稲み抄布): 50% off of the full fare
// discount[ 7 ]: Military Ticket (瓁布):               5% off of the full fare

const int maxNumReservations = 1000;

int enterChoice();

// perform booking
void booking();

// choose arrival airport by input its code, and assign the code to arrivalAirport
void chooseArrivalAirport( int departureAirport, int &arrivalAirport );

// input the departure date
void inputDepartureDate( char date[], int &departureDayWeek );

// return the number of days between currentDate and departureDate
int difference( Date departureDate, Date currentDate );

bool leapYear( int year );

// load all flights from Flight Schedule.dat and put them into the array flights
void loadFlightSchedules( Flight flights[], int &numFlights );

// load all flights from departureAirport to arrivalAirport,
// and put them into the array flights
void loadFlightSchedules( Flight flights[], int &numFlights,
     int departureAirport, int arrivalAirport, int departureDayWeek );

// load all flightSeats from departureAirport to arrivalAirport on departureDate,
// and put them into the array flightSeats
void loadFlightSeats( FlightSeats flightSeats[], int &numFlightSeats, char departureDate[],
                     int departureAirport, int arrivalAirport );

// display all flights from departureAirport to arrivalAirport
void displayFlights( const Flight flights[], int numFlights,
                    FlightSeats flightSeats[], int &numFlightSeats,
                    int departureAirport, int arrivalAirport, char date[] );

// choose a flight by input its number,
// and assign the number to reservation.flightNo
void chooseFlight( Reservation &reservation, const Flight flights[], int numFlights );

// input the number of tickets for each ticket type,
// and assign them to reservation.tickets
void inputNumTickets( Reservation &reservation, FlightSeats flightSeats[], int &numFlightSeats );

// during booking and refund application,
// the corresponding availableSeats in Flight Seats.dat should be modified
void modifyFlightSeatsFile( Reservation &reservation, int totalNumTickets );

void displayReservation( const Reservation reservation,
                        const Flight flights[], int numFlights );

// append reservation to the end of Reservations.dat
void saveReservation( const Reservation reservation );

// perform booking inquiry
bool bookingInquiry( const char id[] );

// perform refund application
void refundApplication();

// load all reservations from Reservations.dat and put them to the array reservations
void loadReservations( Reservation reservations[], int &numReservations );

int main()
{
   cout << "Welcome to UNI Air Domestic Flights Booking System\n";
   char id[ 12 ];
   int choice;

   while( ( choice = enterChoice() ) != 4 )
   {
      switch( choice )
      {
      case 1:
         booking(); // perform booking
         break;
      case 2:
         cout << "\nEnter ID number: ";
         cin >> id;
         bookingInquiry( id ); // perform booking inquiry
         break;
      case 3:
         refundApplication(); // perform refund application
         break;

      default:
         cerr << "\nInput error!\n";
         break;
      }
   }

   cout << endl;
   system( "pause" );
}

int enterChoice()
{
   cout << "\nInput your choice:\n"
        << "1. Booking\n"
        << "2. Booking enquiry\n"
        << "3. Refund application\n"
        << "4. End\n? ";

   int menuChoice;
   cin >> menuChoice;
   return menuChoice;
}

// perform booking
void booking()
{
    // choose departure airport by input its code,
    // and assign the code to departureAirport
    int departureAirport;
    do {
        cout << "\nDeparture airport:\n";
        for (int i = 1; i <= 11; i++)
            cout << setw(2) << i << ". " << airportName[i] << endl;
        cout << "? ";

        cin >> departureAirport;
    } while (departureAirport < 1 || departureAirport > 11);

    int arrivalAirport;
    // choose arrival airport by input its code, and assign the code to arrivalAirport
    chooseArrivalAirport(departureAirport, arrivalAirport);

    Reservation reservation = { "", "", "", "", "", 0, 0, 0, 0, 0, 0, 0, 0 };

    int departureDayWeek; // departureDayWeek == 0 if departure date is Sunday
    // departureDayWeek == 1 if departure date is Monday
    // departureDayWeek == 2 if departure date is Tuesday
    // departureDayWeek == 3 if departure date is Wednesday
    // departureDayWeek == 4 if departure date is Thursday
    // departureDayWeek == 5 if departure date is Friday
    // departureDayWeek == 6 if departure date is Saturday

    inputDepartureDate(reservation.date, departureDayWeek);

    Flight flights[20];
    int numFlights = 0;

    // load all flights from departureAirport to arrivalAirport,
    // and put them into the array flights
    loadFlightSchedules(flights, numFlights, departureAirport, arrivalAirport,
        departureDayWeek);

    if (numFlights == 0)
    {
        cout << "No flights available!\n";
        return;
    }

    FlightSeats flightSeats[20];
    int numFlightSeats = 0;

    loadFlightSeats(flightSeats, numFlightSeats, reservation.date,
        departureAirport, arrivalAirport);

    int maxNumSeats = 0;
    for (int i = 1; i <= numFlights; i++)
        if (maxNumSeats < flightSeats[i].availableSeats)
            maxNumSeats = flightSeats[i].availableSeats;

    if (maxNumSeats == 0)
    {
        cout << "No seats available for Selected Flight!\n";
        return;
    }

    // display all flights from departureAirport to arrivalAirport
    displayFlights(flights, numFlights, flightSeats, numFlightSeats,
        departureAirport, arrivalAirport, reservation.date);

    // choose a flight by input its number, and assign the number to reservation.flightNo
    chooseFlight(reservation, flights, numFlights);

    // input the number of tickets for each ticket type,
    // and assign them to reservation.tickets
    inputNumTickets(reservation, flightSeats, numFlightSeats);

    int totalNumTickets = -reservation.tickets[3];
    for (int i = 1; i < 8; i++)
        totalNumTickets += reservation.tickets[i];

    if (totalNumTickets > 0)
        modifyFlightSeatsFile(reservation, totalNumTickets);
    else
    {
        cout << "Your booking could not be completed!\n";
        return;
    }

    displayReservation(reservation, flights, numFlights);

    cout << "\nID number: ";
    cin >> reservation.id;
    cout << "\nName: ";
    cin >> reservation.name;
    cout << "\nMobile: ";
    cin >> reservation.mobile;

    // append reservation to the end of Reservations.dat
    saveReservation(reservation);

    cout << "\nBooking completed!\n";
}

// choose arrival airport by input its code, and assign the code to arrivalAirport
void chooseArrivalAirport( int departureAirport, int &arrivalAirport )
{
    do
    {
        cout << "\nArrival airport:\n";
        for (int i = 1; i < 12; i++)
            if (fullFare[departureAirport][i])
                cout << setw(2) << i << ". " << airportName[i] << endl;
        cout << "? ";
        cin >> arrivalAirport;
    } while (!(arrivalAirport >= 1 && arrivalAirport <= 11 && fullFare[departureAirport][arrivalAirport]));


}

void inputDepartureDate( char date[], int &departureDayWeek )
{
   tm structuredTime;
   time_t rawTime = time( nullptr );
   localtime_s( &structuredTime, &rawTime );

   int year = structuredTime.tm_year + 1900;
   int month = structuredTime.tm_mon + 1;
   int day = structuredTime.tm_mday;
   
   int dayOfMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
   //1 -> 31 2 -> 28 3 -> 30 ... 12->31
   int choice;
   do
   {
       int tempYear = year;
       int tempMonth = month;
       cout << "\nDeparture Date (Month):\n";
       for (int i = 1; i <= 6; i++)
       {
           cout << i << ". " << tempYear << '-' << tempMonth++ << endl;
           if (tempMonth > 12)
           {
               tempMonth = 1;
               ++tempYear;
           }
       }
       cout << "? ";
       cin >> choice;
   } while (!(choice >= 1 && choice <= 6));

   Date flightDate;
   flightDate.year = month + choice - 1 > 12 ? year+1 : year;
   flightDate.month = month + choice - 1 > 12 ? month + choice - 13 : month + choice - 1;

   //judge Feb
   if (leapYear(flightDate.year))
       dayOfMonth[2] = 29;
   int beginDay = flightDate.month == month ? day : 1;
   int endDay = dayOfMonth[flightDate.month];
   //reset Feb
   dayOfMonth[2] = 28;

   do
   {
       cout << "\nDay (" << beginDay << " ~ " << endDay << "): ";
       cin >> flightDate.day;
       cout << endl;
   } while (flightDate.day<beginDay || flightDate.day>endDay);

   //deal date
   int index = 0;
   date[index++] = flightDate.year / 1000 + '0';
   date[index++] = flightDate.year % 1000 / 100 + '0';
   date[index++] = flightDate.year % 100 / 10 + '0';
   date[index++] = flightDate.year % 10 + '0';
   date[index++] = '/';
   if (flightDate.month > 9)
       date[index++] = flightDate.month / 10 + '0';
   date[index++] = flightDate.month % 10 + '0';
   date[index++] = '/';
   if (flightDate.day > 9)
       date[index++] = flightDate.day / 10 + '0';
   date[index++] = flightDate.day % 10 + '0';
   date[index++] = '\0';

   Date currentDate;
   currentDate.year = year;
   currentDate.month = month;
   currentDate.day = day;
   
   //deal dayweek
   int differDay = difference(flightDate, currentDate);
   departureDayWeek = structuredTime.tm_wday + differDay % 7;
   if (departureDayWeek < 7)
       return;
   departureDayWeek -= 7;

}

int difference( Date departureDate, Date currentDate )
{
    
    int departure_dayOfMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int current_dayOfMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (leapYear(departureDate.year))
        departure_dayOfMonth[2] = 29;
    if (leapYear(currentDate.year))
        current_dayOfMonth[2] = 29;

    //compute
    int differDay = 0;
    if (departureDate.year == currentDate.year)
    {
        //the same day
        if (departureDate.month == currentDate.month)
        {
            if (departureDate.day == currentDate.day)
                return 0;
            else
                return departureDate.day - currentDate.day;
        }

        differDay = current_dayOfMonth[currentDate.month] - currentDate.day;
        for (int i = currentDate.month + 1; i < departureDate.month; i++)
            differDay += current_dayOfMonth[i];
        differDay += departureDate.day;
    }
    else
    {
        bool nowisCurrentYear = 1;
        differDay = current_dayOfMonth[currentDate.month] - currentDate.day;
        ++currentDate.month;
        if (currentDate.month > 12)
        {
            currentDate.month = 1;
            nowisCurrentYear = 0;
        }
        while (departureDate.month != currentDate.month)
        {
            if (nowisCurrentYear)
                differDay += current_dayOfMonth[currentDate.month++];
            else
                differDay += departure_dayOfMonth[currentDate.month++];
            //change year
            if (currentDate.month > 12)
            {
                currentDate.month = 1;
                nowisCurrentYear = 0;
            }
        }
        differDay += departureDate.day;
    }
    return differDay;
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

// load all flights from Flight Schedule.dat and put them into the array flights
void loadFlightSchedules( Flight flights[], int &numFlights )
{
    ifstream inFile("Flight Schedule.dat", ios::binary);
    if (!inFile)
    {
        cerr << "Flight Schedule.dat could not be opened.\n";
        exit(1);
    }

    inFile.seekg(0, ios::end);
    numFlights = inFile.tellg() / sizeof(Flight);
    inFile.seekg(0, ios::beg);
    for(int i = 1;i<=numFlights;i++)
        inFile.read(reinterpret_cast<char*>(&flights[i]), sizeof(Flight));
    inFile.close();

}

// load all flights from departureAirport to arrivalAirport,
// and put them into the array flights
void loadFlightSchedules( Flight flights[], int &numFlights,
     int departureAirport, int arrivalAirport, int departureDayWeek )
{

    Flight allFlights[126]; //allflights.size should bigger than numFlights otherwise numFlights will be 893006897
    int allnumFlights;
    loadFlightSchedules(allFlights, allnumFlights);

    for (int i = 1; i <= allnumFlights; i++)
        if (allFlights[i].departureAirport == departureAirport && allFlights[i].arrivalAirport == arrivalAirport && allFlights[i].dayWeek[departureDayWeek])
            flights[++numFlights] = allFlights[i];
        

}

void loadFlightSeats( FlightSeats flightSeats[], int &numFlightSeats, char departureDate[],
     int departureAirport, int arrivalAirport )
{
    ifstream inFile("Flight Seats.dat", ios::binary);
    if (!inFile)
    {
        cerr << "Flight Seats.dat could not be opened.";
        exit(1);
    }
    int allNumFlightSeats;
    inFile.seekg(0, ios::end);
    allNumFlightSeats = inFile.tellg() / sizeof(FlightSeats);
    FlightSeats temp;
    inFile.seekg(0, ios::beg);
    for (int i = 1; i <= allNumFlightSeats; i++)
    {
        inFile.read(reinterpret_cast<char*>(&temp), sizeof(FlightSeats));
        if (strcmp(temp.date, departureDate) == 0 && temp.departureAirport == departureAirport && temp.arrivalAirport == arrivalAirport)
            flightSeats[++numFlightSeats] = temp;
    }
    inFile.close();



}

// display all flights from departureAirport to arrivalAirport
void displayFlights( const Flight flights[], int numFlights,
                   FlightSeats flightSeats[], int &numFlightSeats,
                    int departureAirport, int arrivalAirport, char date[] )
{
   cout << airportName[ departureAirport ] << " to " << airportName[ arrivalAirport ]
        << " / Depart date: " << date << ".\n\n";
   cout << "Flight   Departure   Arrival   Fare   No. Available Seats\n";

   for( int i = 1; i <= numFlights; i++ )
      if( flightSeats[ i ].availableSeats  > 0 )
         cout << setw( 6 ) << flights[ i ].flightNo
              << setw( 12 ) << flights[ i ].departureTime
              << setw( 10 ) << flights[ i ].arrivalTime
              << setw( 7 ) << fullFare[ departureAirport ][ arrivalAirport ]
              << setw( 22 ) << flightSeats[ i ].availableSeats << endl;
}

// choose a flight by input its number, and assign the number to reservation.flightNo
void chooseFlight( Reservation &reservation, const Flight flights[], int numFlights )
{

    while (1)
    {
        cout << "\nFlight number: ";
        cin >> reservation.flightNo;
        for (int i = 1; i <= numFlights; i++)
            if (strcmp(reservation.flightNo, flights[i].flightNo) == 0)
                return;
    }


}

// input the number of tickets for each ticket type, and assign them to reservation.tickets
void inputNumTickets( Reservation &reservation, FlightSeats flightSeats[], int &numFlightSeats )
{
   int i;
   for( i = 1; i <= numFlightSeats; i++ )
      if( strcmp( reservation.flightNo, flightSeats[ i ].flightNo ) == 0 )
         break;

   int numAvailableSeats = flightSeats[ i ].availableSeats;
   int maxNumTickets = ( numAvailableSeats < 4 ) ? numAvailableSeats : 4;

   do {
      cout << "\nNumber of infant tickets (0 ~ " << maxNumTickets << "): ";
      cin >> reservation.tickets[ 3 ];
   } while( reservation.tickets[ 3 ] < 0 || reservation.tickets[ 3 ] > maxNumTickets );

   int numTickets = 0;
   int numAdults = 0;
   do
   {
      numTickets = 0;

      cout << "\nNumber of full fare tickets (0 ~ " << maxNumTickets << "): ";
      cin >> reservation.tickets[ 1 ];
      numTickets += reservation.tickets[ 1 ];

      cout << "\nNumber of child tickets (0 ~ " << maxNumTickets << "): ";
      cin >> reservation.tickets[ 2 ];
      numTickets += reservation.tickets[ 2 ];

      cout << "\nNumber of senior citizen tickets (0 ~ " << maxNumTickets << "): ";
      cin >> reservation.tickets[ 4 ];
      numTickets += reservation.tickets[ 4 ];

      cout << "\nNumber of impaired tickets (0 ~ " << maxNumTickets << "): ";
      cin >> reservation.tickets[ 5 ];
      numTickets += reservation.tickets[ 5 ];

      cout << "\nNumber of impaired companion tickets (0 ~ " << maxNumTickets << "): ";
      cin >> reservation.tickets[ 6 ];
      numTickets += reservation.tickets[ 6 ];

      cout << "\nNumber of military tickets (0 ~ " << maxNumTickets << "): ";
      cin >> reservation.tickets[ 7 ];
      numTickets += reservation.tickets[ 7 ];

      numAdults = reservation.tickets[ 1 ] + reservation.tickets[ 4 ] +
                 reservation.tickets[ 5 ] + reservation.tickets[ 6 ] +
                 reservation.tickets[ 7 ];

      if( numTickets > maxNumTickets )
         cout << "\nYou can books a maximum of " << maxNumTickets
              << " passengers ( including children ).\n";
      else if( numAdults < reservation.tickets[ 3 ] )
         cout << "\nEach infant must always be accompanied by at least one adult.\n";
   } while( numTickets > maxNumTickets || numAdults < reservation.tickets[ 3 ] );

   cout << endl;
}

void modifyFlightSeatsFile(Reservation& reservation, int totalNumTickets)
{ 
    fstream inoutFile("Flight Seats.dat", ios::in | ios::out | ios::binary);
    if (!inoutFile)
    {
        cerr << "Flight Seats.dat could not be opened.\n";
        exit(1);
    }
    FlightSeats temp;
    inoutFile.seekg(0, ios::end);
    int allnumFlightSeats = inoutFile.tellg() / sizeof(FlightSeats);
    inoutFile.seekg(0, ios::beg);
    for (int i = 0; i < allnumFlightSeats; i++)
    {
        //cout << "Before seek: " << inoutFile.tellg() / sizeof(FlightSeats) << endl;
        //inoutFile.seekg(i * sizeof(FlightSeats), ios::beg);
        //cout << "Before read: "<< inoutFile.tellg() / sizeof(FlightSeats) << endl;
        inoutFile.read(reinterpret_cast<char*>(&temp), sizeof(FlightSeats));
        //cout << "Afore read: " << inoutFile.tellg() / sizeof(FlightSeats) << endl;
        //cout << temp.date << "  " << temp.flightNo << endl;
        if (strcmp(temp.date, reservation.date) == 0 && strcmp(temp.flightNo, reservation.flightNo) == 0)
        {
            //can't adjust a number of data
           // cout << inoutFile.tellg() / sizeof(FlightSeats) << endl;
            inoutFile.seekg(i * sizeof(FlightSeats), ios::beg);
            temp.availableSeats -= totalNumTickets;
            //cout << inoutFile.tellg() / sizeof(FlightSeats)<<endl;
            inoutFile.write(reinterpret_cast<char*>(&temp), sizeof(FlightSeats));
            //cout << inoutFile.tellg() / sizeof(FlightSeats) << endl;
            //inoutFile.seekg(0, ios::cur);
            //cout << inoutFile.tellg() / sizeof(FlightSeats) << endl;
            inoutFile.close();
            return;
        }
    }
}

void displayReservation( const Reservation reservation,
                         const Flight flights[], int numFlights )
{
   int k;
   for( k = 1; k <= numFlights; k++ )
      if( strcmp( reservation.flightNo, flights[ k ].flightNo ) == 0 )
         break;

   cout << "Ticket information:\n\n";
   cout << "Date: " << reservation.date << endl;
   cout << "Flight: B7-" << reservation.flightNo << endl << endl;

   int departureAirport = flights[ k ].departureAirport;
   int arrivalAirport = flights[ k ].arrivalAirport;

   cout << setw( 9 ) << right << airportName[ departureAirport ] << " -> "
        << setw( 9 ) << left << airportName[ arrivalAirport ] << endl;

   cout << setw( 9 ) << right << flights[ k ].departureTime << "    ";
   cout << setw( 9 ) << left << flights[ k ].arrivalTime << endl << endl;

   char ticketType[ 8 ][ 24 ] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                      "Senior Citizen Fare",     "Impaired Fare",
                                      "Impaired Companion Fare", "Military Fare" };

   int total = 0;
   int fare;
   for( int i = 1; i <= 7; i++ )
      if( reservation.tickets[ i ] > 0 )
      {
         fare = fullFare[ departureAirport ][ arrivalAirport ] * discount[ i ] / 100;
         total += ( fare * reservation.tickets[ i ] );
         cout << right << setw( 23 ) << ticketType[ i ] << "  TWD "
              << setw( 4 ) << fare << " x " << reservation.tickets[ i ] << endl;
      }

   cout << "\nTotal: " << total << endl;
}

// append reservation to the end of Reservations.dat
void saveReservation( const Reservation reservation )
{
    ofstream outFile("Reservations.dat", ios::app, ios::binary);
    outFile.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));
    outFile.close();


}

// perform booking inquiry
bool bookingInquiry( const char id[] )
{
    Reservation reservations[maxNumReservations];
    int numReservations;
    loadReservations(reservations, numReservations);

    Flight allflights[126];  //allflights.size should bigger than numFlights otherwise numFlights will be 893006897
    int allnumFlights;
    loadFlightSchedules(allflights, allnumFlights);

    int index = 0;
    for (int i = 1; i <= numReservations; i++)
    {
        if (strcmp(id, reservations[i].id) == 0)
        {
            cout << endl << ++index << ".  ";
            displayReservation(reservations[i], allflights, allnumFlights);
        }
    }
    if (index)
        return 1;
    else
    {
        cout << "\nNo reservations!\n";
        return 0;
    }

}

// perform refund application
void refundApplication()
{
   char id[ 12 ];

   cout << "\nEnter ID number: ";
   cin >> id;

   if( !bookingInquiry( id ) )
      return;

   int choice;
   cout << "\nEnter your choice: ";
   cin >> choice;

   Reservation reservations[ maxNumReservations ];
   int numReservations;
   loadReservations( reservations, numReservations );

   ofstream outFile("Reservations.dat", ios::binary);
   int index = 1;
   bool errortInput = 1;
   for (int i = 1; i <= numReservations; i++)
   {
       if (strcmp(reservations[i].id, id) == 0)
       {
           if (index++ == choice)
           {
               int totalNumTickets = -reservations[i].tickets[3];
               for (int j = 1; j < 8; j++)
                   totalNumTickets += reservations[i].tickets[j];
               modifyFlightSeatsFile(reservations[i], -totalNumTickets);
               errortInput = 0;
               continue;
           }
       }
       outFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
   }
   outFile.close();

   if (errortInput)
   {
       cout << "\nNo this reservation.\n";
       return;
   }



   cout << "\nThe seleted booking has been deleted.\n";
}

// load all reservations from Reservations.dat and put them to the array reservations
void loadReservations( Reservation reservations[], int &numReservations )
{

    ifstream inFile("Reservations.dat", ios::binary);
    if (!inFile)
    {
        cerr << "Reservations.dat could not be opende.\n";
        exit(1);
    }
    inFile.seekg(0, ios::end);
    numReservations = inFile.tellg() / sizeof(Reservation);
    inFile.seekg(0, ios::beg);
    for (int i = 1; i <= numReservations; i++)
        inFile.read(reinterpret_cast<char*>(&reservations[i]), sizeof(Reservation));
    inFile.close();


}