#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "DialogueEdGraphSchema.generated.h"

class UDialogueEdNode; 
class UDialogueEdEdge; 
class UDialogueEdge; 
class UDialogueNode_Base; 

USTRUCT()
struct FDialogueAssetSchemaAction_NewSceneNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:
	FDialogueAssetSchemaAction_NewSceneNode() : NodeTemplate(nullptr) {}

	FDialogueAssetSchemaAction_NewSceneNode(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NodeTemplate(nullptr) {}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	UDialogueEdNode* NodeTemplate;
};

USTRUCT()
struct FDialogueAssetSchemaAction_NewInteractiveNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:
	FDialogueAssetSchemaAction_NewInteractiveNode() : NodeTemplate(nullptr) {}

	FDialogueAssetSchemaAction_NewInteractiveNode(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NodeTemplate(nullptr) {}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	UDialogueEdNode* NodeTemplate;
};

USTRUCT()
struct FDialogueAssetSchemaAction_NewEdge : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:
	FDialogueAssetSchemaAction_NewEdge() : NodeTemplate(nullptr) {}

	FDialogueAssetSchemaAction_NewEdge(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NodeTemplate(nullptr) {}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	UDialogueEdEdge* NodeTemplate;
};

UCLASS()
class UDialogueEdGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:

	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;

	void GetBreakLinkToSubMenuActions(class UToolMenu* Menu, class UEdGraphPin* InGraphPin);

	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;

	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const override;

	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;

	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;

	virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;

	virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;

	virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;

	virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;

	virtual int32 GetCurrentVisualizationCacheID() const override;

	virtual void ForceVisualizationCacheClear() const override;

private:
	static int32 CurrentCacheRefreshID;
};