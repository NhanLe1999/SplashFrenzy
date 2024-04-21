<GameFile>
  <PropertyGroup Name="CaculateQuickMainMenuScene" Type="Layer" ID="b8333f93-2c68-474e-b22c-bbc7900d2aab" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" CustomClassName="CaculateQuickMainMenuScene" Tag="14" ctype="GameLayerObjectData">
        <Size X="1024.0000" Y="768.0000" />
        <Children>
          <AbstractNodeData Name="menu" ActionTag="-1738938054" Tag="203" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" ClipAble="True" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="1024.0000" Y="768.0000" />
            <Children>
              <AbstractNodeData Name="bg" ActionTag="62819756" CallBackType="Touch" CallBackName="onTouch" Tag="202" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-628.0000" RightMargin="-628.0000" TopMargin="-156.0000" BottomMargin="-156.0000" TouchEnable="True" LeftEage="752" RightEage="752" TopEage="356" BottomEage="356" Scale9OriginX="752" Scale9OriginY="356" Scale9Width="776" Scale9Height="368" ctype="ImageViewObjectData">
                <Size X="2280.0000" Y="1080.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="512.0000" Y="384.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="2.2266" Y="1.4063" />
                <FileData Type="Normal" Path="CaculateQuick/Home_bgr.jpg" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="play_button" ActionTag="-549240132" ZOrder="2" CallBackType="Click" CallBackName="onPlayButtonClicked" Tag="16" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="259.5000" RightMargin="259.5000" TopMargin="389.3792" BottomMargin="190.6208" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="5" BottomEage="5" Scale9OriginX="15" Scale9OriginY="5" Scale9Width="475" Scale9Height="178" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="505.0000" Y="188.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="512.0000" Y="284.6208" />
                <Scale ScaleX="0.6500" ScaleY="0.6500" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3706" />
                <PreSize X="0.4932" Y="0.2448" />
                <TextColor A="255" R="65" G="65" B="70" />
                <NormalFileData Type="Normal" Path="CaculateQuick/Play.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="list_top" ActionTag="-1392744679" Tag="81" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="323.9400" RightMargin="323.9400" TopMargin="600.5888" BottomMargin="87.4112" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ScrollDirectionType="0" ItemMargin="30" VerticalType="Align_Bottom" ctype="ListViewObjectData">
                <Size X="376.1200" Y="80.0000" />
                <Children>
                  <AbstractNodeData Name="rank" ActionTag="516372189" CallBackType="Click" CallBackName="onLeaderBoardButtonClicked" Tag="21" IconVisible="False" RightMargin="272.1200" TopMargin="-30.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="5" BottomEage="5" Scale9OriginX="15" Scale9OriginY="5" Scale9Width="74" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="104.0000" Y="110.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position Y="55.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition Y="0.6875" />
                    <PreSize X="0.2765" Y="1.3750" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <NormalFileData Type="Normal" Path="CaculateQuick/btn_Top.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="tutorial_button" ActionTag="-626570110" ZOrder="1" CallBackType="Click" CallBackName="onTutorialButtonClicked" Tag="54" IconVisible="False" LeftMargin="134.0000" RightMargin="138.1200" TopMargin="-30.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="5" BottomEage="5" Scale9OriginX="15" Scale9OriginY="5" Scale9Width="74" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="104.0000" Y="110.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="186.0000" Y="55.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4945" Y="0.6875" />
                    <PreSize X="0.2765" Y="1.3750" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <NormalFileData Type="Normal" Path="CaculateQuick/btn_huongdan.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="btn_setting" ActionTag="-1871274865" ZOrder="2" CallBackType="Click" CallBackName="onSettingButtonClicked" Tag="163" IconVisible="False" LeftMargin="268.0000" RightMargin="4.1200" TopMargin="-30.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="5" BottomEage="5" Scale9OriginX="15" Scale9OriginY="5" Scale9Width="74" Scale9Height="100" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="104.0000" Y="110.0000" />
                    <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                    <Position X="372.0000" Y="55.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.9890" Y="0.6875" />
                    <PreSize X="0.2765" Y="1.3750" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <NormalFileData Type="Normal" Path="CaculateQuick/btn-Setting.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="512.0000" Y="127.4112" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.1659" />
                <PreSize X="0.3673" Y="0.1042" />
                <SingleColor A="255" R="150" G="150" B="255" />
                <FirstColor A="255" R="150" G="150" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="play_layout" ActionTag="-1134605415" Tag="64" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="17.0000" RightMargin="17.0000" TopMargin="503.5000" BottomMargin="73.5000" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
                <Size X="990.0000" Y="191.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="512.0000" Y="169.0000" />
                <Scale ScaleX="1.0313" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.2201" />
                <PreSize X="0.9668" Y="0.2487" />
                <SingleColor A="255" R="150" G="200" B="255" />
                <FirstColor A="255" R="150" G="200" B="255" />
                <EndColor A="255" R="255" G="255" B="255" />
                <ColorVector ScaleY="1.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="512.0000" Y="384.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>