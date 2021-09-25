#include "SDialogueGraphNode.h"
#include "SGraphPin.h"
#include "Widgets/SBoxPanel.h"
#include "DialogueEdNode.h"
#include "DialogueGraphColors.h"
#include "GraphEditorSettings.h"
#include "SlateOptMacros.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

class SDialogueGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	{
		this->SetCursor(EMouseCursor::Default);

		bShowLabel = true;

		GraphPinObj = InPin;
		check(GraphPinObj != nullptr);

		const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
		check(Schema);

		SBorder::Construct(SBorder::FArguments()
			.BorderImage(this, &SDialogueGraphPin::GetPinBorder)
			.BorderBackgroundColor(this, &SDialogueGraphPin::GetPinColor)
			.OnMouseButtonDown(this, &SDialogueGraphPin::OnPinMouseDown)
			.Cursor(this, &SDialogueGraphPin::GetPinCursor)
		);
	}

protected:
	virtual FSlateColor GetPinColor() const override
	{
		return DialogueGraphColors::Pin::Default;
	}

	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override
	{
		return SNew(STextBlock);
	}

	const FSlateBrush* GetPinBorder() const
	{
		return (IsHovered())
			? FEditorStyle::GetBrush(TEXT("Graph.StateNode.Pin.BackgroundHovered"))
			: FEditorStyle::GetBrush(TEXT("Graph.StateNode.Pin.Background"));
	}
};

/////////////////////////////////////////////////////
// SDialogueGraphNode

void SDialogueGraphNode::Construct(const FArguments& InArgs, UDialogueEdNode* InNode)
{
	this->GraphNode = InNode;

	this->SetCursor(EMouseCursor::CardinalCross);

	this->UpdateGraphNode();
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDialogueGraphNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const FSlateBrush* NodeTypeIcon = GetNameIcon();

	FLinearColor TitleShadowColor(0.6f, 0.6f, 0.6f);
	TSharedPtr<SErrorText> ErrorText;
	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
		.Padding(0)
		.BorderBackgroundColor(this, &SDialogueGraphNode::GetBorderBackgroundColor)
		[
			SNew(SOverlay)

			// PIN AREA
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(RightNodeBox, SVerticalBox)
		]

	// STATE NAME AREA
	+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(10.0f)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.ColorSpill"))
		.BorderBackgroundColor(this, &SDialogueGraphNode::GetBackgroundColor)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Visibility(EVisibility::SelfHitTestInvisible)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			// POPUP ERROR MESSAGE
			SAssignNew(ErrorText, SErrorText)
			.BackgroundColor(this, &SDialogueGraphNode::GetErrorColor)
		.ToolTipText(this, &SDialogueGraphNode::GetErrorMsgToolTip)
		]
	+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SImage)
			.Image(NodeTypeIcon)
		]
	+ SHorizontalBox::Slot()
		.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(InlineEditableText, SInlineEditableTextBlock)
			.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
		.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
		.OnVerifyTextChanged(this, &SDialogueGraphNode::OnVerifyNameTextChanged)
		.OnTextCommitted(this, &SDialogueGraphNode::OnNameTextCommited)
		.IsReadOnly(this, &SDialogueGraphNode::IsNameReadOnly)
		.IsSelected(this, &SDialogueGraphNode::IsSelectedExclusively)
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		[
			NodeTitle.ToSharedRef()
		]
		]
		]
		]
		]
		];

	ErrorReporting = ErrorText;
	ErrorReporting->SetError(ErrorMsg);
	CreatePinWidgets();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDialogueGraphNode::CreatePinWidgets()
{
	UDialogueEdNode* Node = CastChecked<UDialogueEdNode>(GraphNode);

	UEdGraphPin* CurPin = Node->GetOutputPin();
	if (!CurPin->bHidden)
	{
		TSharedPtr<SGraphPin> NewPin = SNew(SDialogueGraphPin, CurPin);

		this->AddPin(NewPin.ToSharedRef());
	}
}

void SDialogueGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));
	RightNodeBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillHeight(1.0f)
		[
			PinToAdd
		];
	OutputPins.Add(PinToAdd);
}


const FSlateBrush* SDialogueGraphNode::GetNameIcon() const
{
	return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Icon"));
}

FSlateColor SDialogueGraphNode::GetBorderBackgroundColor() const
{
	return DialogueGraphColors::NodeBorder::Root;
}

FSlateColor SDialogueGraphNode::GetBackgroundColor() const
{
	UDialogueEdNode* MyNode = CastChecked<UDialogueEdNode>(GraphNode);
	return MyNode ? MyNode->GetBackgroundColor() : FLinearColor(0.08f, 0.08f, 0.08f);
}

EVisibility SDialogueGraphNode::GetDragOverMarkerVisibility() const
{
	return EVisibility::Visible;
}