Page({
  data: {
   temp:0,
   hum:0
  },
  // 事件处理函数
  getinfo(){
    var that = this
    wx.request({
    url: "https://api.heclouds.com/devices/1055107638/datapoints",   
    //将请求行中的数字换成自己的设备ID
    header: {
      "api-key": "0HbIQSxc7MAdROLYHrVCfBvLZBk=" //自己的api-key
    },
    method: "GET",
  success: function (res) {
    console.log("获取成功", res);
    that.setData({
     temp: res.data.data.datastreams[4].datapoints[0].value,
     hum: res.data.data.datastreams[1].datapoints[0].value,
     co2: res.data.data.datastreams[6].datapoints[0].value,
     tvoc: res.data.data.datastreams[0].datapoints[0].value,
     sun: res.data.data.datastreams[9].datapoints[0].value,
    });
    console.log("temp==", that.data.temp);
    console.log("hum==", that.data.hum);
    console.log("co2==", that.data.co2);
    console.log("tvoc==", that.data.tvoc);
    console.log("sun==", that.data.sun);

    }
   });
  },

  onLoad() {
    var that = this
    setInterval(function(){
      that.getinfo()
    },1000)
  }
})
