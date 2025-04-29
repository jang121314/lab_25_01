# lab_25_01

프로젝트: document 해석기 만들기


배경: cpp 객체 지향  프로그래밍 팀 프로젝트 과제 도중 4월 7일 아침경 프로젝트 파일 전부 손실 이에, 더 빠른 속도로 작업하기 위해서 여러 원칙 적용해서 프로젝트 개발 진행

한 파일에 작업: 이는 여러 파일을 오가며 작업하기에는 비효율적이라고 판단
error 처리는 단순한 int: 이전 프로젝트에서는 error 클래스를 만들어서 했으나 쓰일일이 없었음
public 위주 작업: 객체 지향의 캡슐화는 한 클래스에 모든 클래스를 박아서 달성하도록 하고 그 안에서는 public으로 열린 방식으로 작업
SDL class는 좀 더 크게: 이전 프로젝트에서는 SDL과 다른 객체들을 구분하고 작업하는 과정에서 시간이 소요, 이에 더 빠른 작업을 위해서 SDL의 기능들은 다른 객체에 있어야할 기능까지도 존재


개요:

document 해석기는 html 5 텍스트 파일을 일부 해석함으로써 그 구조를 익히기 위해서 제작하였습니다. 
Style class 등에서 상당한 양의 상속과 다형성 생성자 오버로딩 등이 구현이 되었습니다
Property class 등에서 operator 오버로딩과 템플릿이 구현이 되었습니다
사용하기 위해서는 ./ .exe ( 읽을 document file ) 형식으로 실행해야 합니다.


구조:

class로는 property style element document SDL class가 있습니다.
SDL > document > element > style > property 구조로 주로 구현이 되었습니다.
주로 std::vector와 property의 동적 할당을 담당하는 클래스 ( 스마트 포인터 구조와 유사 ) 와 stack에 저장되는 영역의 변수들을 저장하는 데이터로 활용하였습니다.

작동 방식:

main: file 파일을 읽습니다.
document: 읽은 데이터를 파싱합니다.
element: document에서 받은 tag 데이터를 파싱합니다. ( 사실 public 상속한 tag가 수행 )
style: element에서 받은 style 속성 데이터를 파싱합니다.
SDL: document class를 받고 이것을 해석하여 화면에 그립니다.
main: 종료시 0을 리턴합니다.


지원하는 것:

element tag: 존재하지 않음 ( 시간 부족으로 구현하지 않음 )
no tag content: string을 저장하는 element 임

style:

width, height: auto도 지원 ( height: auto 등에 버그 존재하나 제거 실패 )
color, background-color, border-color: 
red, green, blue, yellow, aqua, magenta, white, black, #ffffff, #ffffffff 등등 지원
border-style: none, solid, double 지원
text-size, padding, margin: int 형식으로 지원
text-align: left, center, right 등 지원

출처:

SDL window, SDL Renderer, SDL font 등등에서 퍼플렉시티에게 물어봄
element tag, style의 속성 등등에서 퍼플렉시티에게 물어봄
UTF-8로 하는 과정에서 퍼플렉시티에게 물어봄


아쉬운 점:

element 수평 수직 정렬 기능을 추가하지 못함, 이는 table를 만들지 못함
SDL에서 document 그리는 기능에 버그가 있음
SDL의 Event 부분에서 캡슐화를 하지 못함
tag 별 기본 style 구현을 하지 못함, 이는 style를 기본적으로 사용해야함
<style></style>를 구현하지 못함, 이는 inline style만 건들수가 있음
<br>를 구현하지 못함, 이는 공백을 그릴수가 없음
style property의 top left down right 등을 구현하지 못함
SDL의 stirngDraw 함수의 구조를 유연하게 하지 못함
주석처리 등등에 부족한 부분이 많음


소감:


virtual function에 대해서 좀 더 학습이 되었다.

virtual function은 부모 클래스의 부분에서 자식 클래스를 호출하기 위한 함수로 자식 클래스에서 상속 받은 부모 클래스의 함수에서 자식 클래스에서 override한 함수들을 호출이 가능하도록 한다.

이와 동시에 부모 클래스의 포인터에서 virtual function은 자식 클래스의 객체 정보를 가질 경우 자식 클래스에서 override 된 해당 함수를 호출하도록 한다.




