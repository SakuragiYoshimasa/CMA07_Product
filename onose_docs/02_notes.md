CV2MIDI の実装に必要な Addon と参考資料
===

参考資料
---
* MIDI
	* [MIDIをopenFrameworksで使ってみる。](http://asus4.hatenablog.com/entry/20101121/1290331567)
	* [ofxMidi使用時のやることメモ](http://qiita.com/y_UM4/items/d40e073190d149853379)
* OpenCV
	* [OpenCV](http://opencv.org)
	* [openFrameworks – addon を使う 3 : OpenCVを利用した映像認識](http://yoppa.org/ma2_10/2214.html)
		* かなり細かく解説されている
		* 豊富な事例集付き
	* [こじ研（openFrameworks）](http://www.myu.ac.jp/~xkozima/lab/ofTutorial5.html)


Addon
---
* [ofxMidi](https://github.com/danomatika/ofxMidi)
* [ofxCv](https://github.com/kylemcdonald/ofxCv)

とりあえずやってみるタスク
---
* それぞれのサンプルプログラムの実行
	* Serato への接続
	* FaceTime Camera を用いた CV サンプルアルゴリズムの確認

クラス設計案
---
* class CardRecognizer
	* ウェブカメラからカードを認識
	* カードの x, y, z 座標を取得
* class ControlMonitor
	* ウェブカメラから取得した情報を画面に表示
* class MidiControl
	* x, y, z 座標を元に，MIDI 制御できる形式に変換

アイデア
---
* 入力としておもしろそうなもの
	* Face Tracker
		* https://github.com/kylemcdonald/ofxFaceTracker



