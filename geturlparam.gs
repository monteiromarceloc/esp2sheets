// get URL param
// https://script.google.com/macros/s/AKfycbzY86fsw9ciDN0c7BLupnCCTP9rPIoo-sKRXbEZ_R0/dev?value=123
// video tutorial: https://www.youtube.com/watch?v=4e9hE34RMZM

function doGet(e) {
  Logger.log(JSON.stringify(e));
  var result = 'OK';
  if(e == 'undefined' || e.parameter == 'undefined'){
    result = 'No parameters';
  }
  else {
    var sheet_id = '1xjG_j9m7yMfDKWsOEdMgcza3hzAUeH39_KwTHcKKL5o';
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1;
    var rowData = [];
    var Curr_Date = new Date();
    rowData[0] = Curr_Date;
    var Curr_Time = Utilities.formatDate(Curr_Date, 'Asia/Jakarta', 'HH:mm:ss');
    rowData[1] = Curr_Time;
    for (var param in e.parameter) { 
      Logger.log('In for loop : ' + param);
      // todo: format message
      var value = e.parameter[param];
      switch(param) { 
        case 'value':
          rowData[2] = value;
          break;
        default:
          result = 'Unsuported Parameter'
      }
      Logger.log(JSON.stringify(rowData));
      var newRange = sheet.getRange(newRow, 1, 1, rowData.length);;
      newRange.setValues([rowData]);
    }
    return ContentService.createTextOutput(result);
  }
}
