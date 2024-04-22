<GameFile>
  <PropertyGroup Name="SFGameScene" Type="Layer" ID="202f8a5d-0fde-49bb-9fbb-f61270744b03" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" CustomClassName="SFGameScene" Tag="14" ctype="GameLayerObjectData">
        <Size X="1024.0000" Y="768.0000" />
        <Children>
          <AbstractNodeData Name="root_layout" ActionTag="-46831262" Tag="193" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1024.0000" Y="768.0000" />
            <Children>
              <AbstractNodeData Name="bg" ActionTag="406390776" Tag="37" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="32.0000" RightMargin="32.0000" TopMargin="114.0000" BottomMargin="114.0000" LeftEage="316" RightEage="316" TopEage="178" BottomEage="178" Scale9OriginX="316" Scale9OriginY="178" Scale9Width="328" Scale9Height="184" ctype="ImageViewObjectData">
                <Size X="960.0000" Y="540.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="512.0000" Y="384.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.9375" Y="0.7031" />
                <FileData Type="Normal" Path="res/BlackPink/background/world_1/world_1_layer_3.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="obj_die_game" ActionTag="1535852297" Tag="23" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="352.0000" RightMargin="352.0000" TopMargin="778.0000" BottomMargin="-105.0000" ctype="SpriteObjectData">
                <Size X="320.0000" Y="95.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                <Position X="512.0000" Y="-10.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="-0.0130" />
                <PreSize X="0.3125" Y="0.1237" />
                <FileData Type="Normal" Path="res/BlackPink/ui/bis_ui_bar_world_1.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="512.0000" Y="384.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="root_game_play" ActionTag="429048893" Tag="37" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1024.0000" Y="768.0000" />
            <Children>
              <AbstractNodeData Name="Panel_1" ActionTag="1854703610" Tag="12" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" TopMargin="7.6800" BottomMargin="-7.6800" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="1024.0000" Y="768.0000" />
                <Children>
                  <AbstractNodeData Name="bg_score" ActionTag="1668230532" ZOrder="1" Tag="268" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="30.7200" RightMargin="673.2800" TopMargin="23.0400" BottomMargin="649.9600" LeftEage="99" RightEage="99" TopEage="29" BottomEage="29" Scale9OriginX="99" Scale9OriginY="29" Scale9Width="122" Scale9Height="37" ctype="ImageViewObjectData">
                    <Size X="320.0000" Y="95.0000" />
                    <Children>
                      <AbstractNodeData Name="txt_score" ActionTag="-620428527" Tag="269" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="109.4280" RightMargin="67.5720" TopMargin="15.5000" BottomMargin="15.5000" FontSize="40" LabelText="500000" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" OutlineSize="2" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="143.0000" Y="64.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="180.9280" Y="47.5000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5654" Y="0.5000" />
                        <PreSize X="0.4469" Y="0.6737" />
                        <FontResource Type="Normal" Path="fonts/new_font.ttf" Plist="" />
                        <OutlineColor A="255" R="192" G="91" B="1" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_1" ActionTag="1235196922" Tag="13" IconVisible="False" LeftMargin="0.4257" RightMargin="224.5743" TopMargin="-1.3811" BottomMargin="1.3811" LeftEage="31" RightEage="31" TopEage="31" BottomEage="31" Scale9OriginX="31" Scale9OriginY="31" Scale9Width="33" Scale9Height="33" ctype="ImageViewObjectData">
                        <Size X="95.0000" Y="95.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="47.9257" Y="48.8811" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1498" Y="0.5145" />
                        <PreSize X="0.2969" Y="1.0000" />
                        <FileData Type="Normal" Path="res/BlackPink/ui/bis_ui_icon_notes_world_1.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleY="1.0000" />
                    <Position X="30.7200" Y="744.9600" />
                    <Scale ScaleX="0.8500" ScaleY="0.8500" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.0300" Y="0.9700" />
                    <PreSize X="0.3125" Y="0.1237" />
                    <FileData Type="Normal" Path="res/BlackPink/ui/bis_ui_bar_world_1.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="bg_diamond" ActionTag="-1078019044" ZOrder="1" Tag="14" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="352.0000" RightMargin="352.0000" TopMargin="23.0400" BottomMargin="649.9600" LeftEage="99" RightEage="99" TopEage="29" BottomEage="29" Scale9OriginX="99" Scale9OriginY="29" Scale9Width="122" Scale9Height="37" ctype="ImageViewObjectData">
                    <Size X="320.0000" Y="95.0000" />
                    <Children>
                      <AbstractNodeData Name="txt_diamond" ActionTag="-1980165529" Tag="15" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="145.4280" RightMargin="103.5720" TopMargin="15.5000" BottomMargin="15.5000" FontSize="40" LabelText="500" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" OutlineSize="2" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                        <Size X="71.0000" Y="64.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="180.9280" Y="47.5000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5654" Y="0.5000" />
                        <PreSize X="0.2219" Y="0.6737" />
                        <FontResource Type="Normal" Path="fonts/new_font.ttf" Plist="" />
                        <OutlineColor A="255" R="192" G="91" B="1" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="Image_1" ActionTag="-2103311156" Tag="16" IconVisible="False" LeftMargin="0.4257" RightMargin="224.5743" TopMargin="-1.3811" BottomMargin="1.3811" LeftEage="31" RightEage="31" TopEage="31" BottomEage="31" Scale9OriginX="31" Scale9OriginY="31" Scale9Width="33" Scale9Height="33" ctype="ImageViewObjectData">
                        <Size X="95.0000" Y="95.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="47.9257" Y="48.8811" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1498" Y="0.5145" />
                        <PreSize X="0.2969" Y="1.0000" />
                        <FileData Type="Normal" Path="res/BlackPink/ui/bis_ui_icon_gem_world_1.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                    <Position X="512.0000" Y="744.9600" />
                    <Scale ScaleX="0.8500" ScaleY="0.8500" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5000" Y="0.9700" />
                    <PreSize X="0.3125" Y="0.1237" />
                    <FileData Type="Normal" Path="res/BlackPink/ui/bis_ui_bar_world_1.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="list_btn" ActionTag="-27273896" Tag="17" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="676.2800" RightMargin="30.7200" TopMargin="23.0400" BottomMargin="649.9600" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ScrollDirectionType="0" ItemMargin="15" VerticalType="Align_VerticalCenter" ctype="ListViewObjectData">
                    <Size X="317.0000" Y="95.0000" />
                    <Children>
                      <AbstractNodeData Name="btn_sound" ActionTag="1866959070" CallBackType="Click" CallBackName="onSoundButtonClicked" Tag="18" IconVisible="False" RightMargin="222.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="65" Scale9Height="73" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="95.0000" Y="95.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="47.5000" Y="47.5000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.1498" Y="0.5000" />
                        <PreSize X="0.2997" Y="1.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <NormalFileData Type="Normal" Path="res/BlackPink/button_world/button_world_1/bis_button_sound_on_world_1.png" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="music" ActionTag="-1294359069" ZOrder="1" CallBackType="Click" Tag="19" IconVisible="False" LeftMargin="110.0000" RightMargin="112.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="65" Scale9Height="73" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="95.0000" Y="95.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="157.5000" Y="47.5000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.4968" Y="0.5000" />
                        <PreSize X="0.2997" Y="1.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <NormalFileData Type="Normal" Path="res/BlackPink/button_world/button_world_1/bis_button_music_on_world_1.png" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                      <AbstractNodeData Name="btn_pause" ActionTag="247841442" ZOrder="2" CallBackType="Click" CallBackName="onPauseButtonClicked" Tag="277" IconVisible="False" LeftMargin="220.0000" RightMargin="2.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="65" Scale9Height="73" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                        <Size X="95.0000" Y="95.0000" />
                        <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                        <Position X="315.0000" Y="95.0000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.9937" Y="1.0000" />
                        <PreSize X="0.2997" Y="1.0000" />
                        <TextColor A="255" R="65" G="65" B="70" />
                        <NormalFileData Type="Normal" Path="res/BlackPink/button_world/button_world_1/bis_button_pause_world_1.png" Plist="" />
                        <OutlineColor A="255" R="255" G="0" B="0" />
                        <ShadowColor A="255" R="110" G="110" B="110" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="1.0000" ScaleY="1.0000" />
                    <Position X="993.2800" Y="744.9600" />
                    <Scale ScaleX="0.8500" ScaleY="0.8500" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.9700" Y="0.9700" />
                    <PreSize X="0.3096" Y="0.1237" />
                    <SingleColor A="255" R="255" G="255" B="255" />
                    <FirstColor A="255" R="150" G="150" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="512.0000" Y="376.3200" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.4900" />
                <PreSize X="1.0000" Y="1.0000" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn_up" ActionTag="73578631" Tag="24" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="822.8000" RightMargin="51.2000" TopMargin="579.6000" BottomMargin="38.4000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="120" Scale9Height="128" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="150.0000" Y="150.0000" />
                <AnchorPoint ScaleX="1.0000" />
                <Position X="972.8000" Y="38.4000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9500" Y="0.0500" />
                <PreSize X="0.1465" Y="0.1953" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Normal" Path="res/BlackPink/control/bis_button_control_up.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn_left" ActionTag="358002267" Tag="25" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="51.2000" RightMargin="822.8000" TopMargin="579.6000" BottomMargin="38.4000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="120" Scale9Height="128" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="150.0000" Y="150.0000" />
                <AnchorPoint />
                <Position X="51.2000" Y="38.4000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0500" Y="0.0500" />
                <PreSize X="0.1465" Y="0.1953" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Normal" Path="res/BlackPink/button_main/left.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="btn_right" ActionTag="-1003946742" Tag="26" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="242.0000" RightMargin="632.0000" TopMargin="579.6000" BottomMargin="38.4000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="120" Scale9Height="128" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="150.0000" Y="150.0000" />
                <AnchorPoint />
                <Position X="242.0000" Y="38.4000" />
                <Scale ScaleX="0.8000" ScaleY="0.8000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.2363" Y="0.0500" />
                <PreSize X="0.1465" Y="0.1953" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Normal" Path="res/BlackPink/button_main/right.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="512.0000" Y="384.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="255" G="255" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>