function getMonthString ( month ) {
  var day = "";
  switch ( month ) {
    case 0:
        day = "Jan";
        break;
    case 1:
        day = "Feb";
        break;
    case 2:
        day = "Mar";
        break;
    case 3:
        day = "Apr";
        break;
    case 4:
        day = "May";
        break;
    case 5:
        day = "Jun";
        break;
    case 6:
        day = "Jul";
        break;
    case 7:
        day = "Aug";
        break;
    case 8:
        day = "Sep";
        break;
    case 9:
        day = "Oct";
        break;
    case 10:
        day = "Nov";
        break;
    case 11:
        day = "Dec";
        break;
  }

  return day;
}

function getYearString ( year ) {
  return year.toString().slice(2,4);
}

function getDateFormattedString ( date ) {
  return getMonthString( date.getUTCMonth() ) + ' ' + date.getDate() + ', ' + getYearString( date.getFullYear() );
}

function getDateString ( timestamp ) {
  var date = new Date( Number(timestamp) );
  return getDateFormattedString( date );
}

function msToSeconds ( milliseconds ) {
  return milliseconds / 1000;
}

function msToMinutes ( milliseconds ) {
  return ( msToSeconds(milliseconds) ) / 60;
}

function msToHours ( milliseconds ) {
  return ( msToMinutes(milliseconds) ) / 60;
}

function msToDays ( milliseconds ) {
  return ( msToHours(milliseconds) ) / 24;
}

function msToYears ( milliseconds ) {
  return ( msToDays(milliseconds) ) / 365.25;
}

function getAge () {
  // June 26, 1990 timestamp in milliseconds - 646383600000
  var bdayTS = 646383600000;
  var diff = Date.now() - bdayTS;
  return parseInt(msToYears(diff));
}
