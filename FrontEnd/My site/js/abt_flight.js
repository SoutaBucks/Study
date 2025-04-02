$(function(){

  // 오늘 날짜를 구하는 함수 "YYYY-MM-DD" 형식
  var getTodday = function() {
    var date = new Date();
    var y_m_d = date.getFullYear() 
              + "-" + (date.getMonth() + 1 > 9 ? date.getMonth() + 1 : "0" + (date.getMonth() + 1))
              + "-" + (date.getDate() > 9 ? date.getDate() : "0" + date.getDate());
    return y_m_d;
  };

  // 오늘 이전으로 날짜 설정 못하고, 도착날은 출발날 이후로만 하도록
  var $departday = $("#depart-arrive-day input[name = depart_day]");
  var $arriveday = $("#depart-arrive-day input[name = arrive_day]");
  var today = getTodday();

  $departday.val(today);
  $departday.attr("min", today);
  $arriveday.on("click", function() {
    $arriveday.attr("min", $departday.val())
  });

  // 왕복, 편도에 따라 화살표 모양과 날짜 선택 개수가 변함
  var oneway_flag = false;  // 날짜 선택 개수를 때문에
  $("#flight-type input").on("click", function(){
    // 출발 도착 날짜, 화살표 변화
    // attr -> 속성 / css -> 디자인 !!!!!!!!!!1
    var $arrow = $("#arrow img");

    if($(this).val() == "roundtrip") {
        $arrow.attr("src", "images/roundtrip.png");
        $arriveday.show();
        oneway_flag = false;
    } 
    else {
        $arrow.attr("src", "images/oneway.png");
        $arriveday.hide();
        oneway_flag = true;
    }
  });

  // 제출하기를 눌렀을 때 양식이 제대로 입력되었는지 확인
  $("#flight_submit_button").on("click", function(event) {
    // 올바르다면 flag는 true
    var flag = true;

    // 인원 수 확인
    if(flag && ($("input[name = adult_cnt]").val() == 0 && $("input[name = child_cnt]").val())) {
      alert("인원은 최소 1명을 선택해야합니다");
      flag = false
    }
    // 출발지 도착지 입력 확인
    var $starting_point = $("#depart-arrive select[name = depart]");
    var $destination = $("#depart-arrive select[name = arrive]");
    
    if(flag && !$starting_point.val()) {
      alert("출발지를 입력해 주십시오");
      flag = false;
    } else if(flag && !$destination.val()) {
      alert("도착지를 입력해 주십시오");
      flag = false;
    }

    // 출발지와 도착지는 같을 수 없다
    if(flag && (($starting_point.val() != null && $destination.val() != null) && ($starting_point.val() == $destination.val()))) {
      alert("출발지와 도착지가 같습니다");
      flag = false;
    }

    // 날짜 입력 확인
    if(!oneway_flag && flag && ($arriveday.val() == "")) {
      alert("도착 날짜를 입력해주십시오");
      flag = false;
    }

    // 잘 되었다면 "아래 정보가 맞습니까?" 출력
    if(flag == true) {
      var finish = confirm("아래 정보가 맞습니까?");
      
      if(finish == true) 
        alert("다음 페이지로 넘어갑니다");
      else 
        event.preventDefault();
    }
    else 
      event.preventDefault();
  });  
});