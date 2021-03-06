/* ----------------------------------------------------------------------------
 *                复选框控件实现
 *因部分编译器显示方式不同,下列的窗口显示若不够清晰,请在其它文本编辑器里打开试试!
 * --------------------------------------------------------------------------*/


//说明:
//不同于常用GUI,此复选框控件已是一个完整的用户模块,如下图所示示例:
//第一屏
//┌────相关配置─────┐
//│  　　 1.□自动背光  　　 ┼
//│ 　　　2.■上电清零     　↓
//└←━━━━━━━━━━━→┘
//最后一屏(含返回附加字时):
//┌────相关配置─────┐
//│  　　 8.□ 循环加热  　　↑
//│ 　　　   [返 回]       　┼
//└←━━━━━━━━━━━→┘
//或(含保存附加字时,集中保存):
//┌────相关配置─────┐
//│  　　 8.□ 循环加热  　　↑
//│   [保  存]    [返 回]    ┼
//└←━━━━━━━━━━━→┘

//图中 :
//←━━━→为水平滚动条,当显示区超过5行时可以有垂直滚动条
//[返 回]为按钮,光标移动到上面可直接返回
//■表示选中该功能,□表示取消选中该功能

//继承关系:
//KCheckbox继承关系为:
//  KCheckbox->TListBoxEx->TListBox->TWidget->(间接继承)TWin
//直接继承时可直接将该结构转换为基类结构后并调用基类相关函数
//间接继承通过该结构提供的间接转函数数转换为基类结构并可调用基类结构函数
//
//因控件已包装好,且基类无特殊说明外(注释带★标志),
//基类直接操作不当可能会影响系统工作,故不建议直接使用基类操作

#ifndef __T_CHECKBOX_H 
#define __T_CHECKBOX_H

/**********************************************************************
                  内部结构
**********************************************************************/
#include "TListboxEx.h"

typedef struct{
  TListboxEx_t ListboxEx;       //基类
  unsigned char SelMask[(TCHECKBOX_ITEM_COUNT + 7) >> 3]; //缓存用户所选对应项的选中状态
  TGUINotify_t cbGUINotify;    //用户通报函数
}TCheckbox_t;

//复选框在Flag里附加有两个自定义可选功能:
#define TCHECKBOX_EN_SAVE     0x01      //允许带保存字
#define TCHECKBOX_EN_RETURN   0x02      //允许带返回字

//通报函数应响应下列类型通报:
//TGUI_NOTIFY_GET_CAPTION 获得标题
//TGUI_NOTIFY_GET_ITEM 若得项显示内容
//TGUI_NOTIFY_KEY_ENTER 每一项的确认键,此时应检查选中与否并进行应用层处理
//若项超过设定希数,表示在附加的保存焦点上
//TGUI_NOTIFY_EKY_ESCAPE 退出到上一层


/**********************************************************************
                          成员函数
**********************************************************************/
//------------------------检查某项是否选中----------------------------
//返回0表示未选中,否则表示选中
unsigned char TCheckbox_IsChecked(TCheckbox_t *pCheckbox,
                                  TItemSize_t Item);

//------------------------置某项为选中状态----------------------------
//返回0表示未选中,否则表示选中
void TCheckbox_SetChecked(TCheckbox_t *pCheckbox,
                          TItemSize_t Item);

//------------------------清除某项选中状态----------------------------
//返回0表示未选中,否则表示选中
void TCheckbox_ClrChecked(TCheckbox_t *pCheckbox,
                          TItemSize_t Item);

//------------------------设置所有状态----------------------------
//每一位表示一个状态,0表示未选中,否则表示选中
void TCheckbox_SetAllCheck(TCheckbox_t *pCheckbox,
                           unsigned char *pCheck,
                           TItemSize_t Items);

//--------------------------得到所有状态--------------------------------
void TCheckbox_GetAllCheck(TCheckbox_t *pCheckbox,
                           unsigned char *pCheck,  //返回的数据
                           TItemSize_t Items);

//-----------------确认键时,判断是否在保存键上--------------------
//当返回的项超过用户设定的项时,即表示在保存键上,略


/**********************************************************************
                          行为函数
**********************************************************************/

//-------------------------初始化函数-----------------------------
//初始化后所有项均被置为未选中状态,应选置选中状态再重画窗口
//注:考虑很多系统仅使用静态内层分配,故将创建函数留给更高一层,即
//可在此基础上立真正的创建函数
void TCheckbox_Init(TCheckbox_t *pCheckbox,  //由用户分配的存储空间
                     TWinHandle_t hWin,         //已建立并初始化好的窗口
                     TItemSize_t Items,         //预定义项目总数
                     TItemSize_t ItemW,         //预定义项宽度(即项的最宽度)
                     unsigned char Flag,        //控件标志
                     TGUINotify_t cbGUINotify); //通报函数

//-------------------------窗口重画所有函数-------------------------
//以此为基础的应用程序(非继承类)初始化完成后调用此函数重画所有
#define  TCheckbox_PaintAll(pCheckbox) \
  do{ListBox_PaintAll((TListbox_t *)(pCheckbox));}while(0)

//-------------------------按键处理函数-----------------------------
//void TCheckbox_Key(TCheckbox_t *pCheckbox,unsigned char Key);
//直接基类实现:
#define TCheckbox_Key(pCheckbox,Key)\
  do{TListboxEx_Key((TListboxEx_t*)pCheckbox,Key);}while(0)

//-------------------------复选框回调实现函数-----------------------------
//仅供内部通报使用
const void* TCheckBox_Notify(void *pvSource,
                             unsigned char Type,
                             const void *pvData);


#endif

